from collections import defaultdict
import csv
import numpy as np
from numpy import genfromtxt
import pickle5 as pickle
import tabulate


def load_data():
    item_train = genfromtxt('datasets/content_item_train.csv', delimiter=',')
    user_train = genfromtxt('datasets/content_user_train.csv', delimiter=',')
    y_train = genfromtxt('datasets/content_y_train.csv', delimiter=',')
    with open('datasets/content_item_train_header.txt', newline='') as f:
        item_features = list(csv.reader(f))[0]
    with open('datasets/content_user_train_header.txt', newline='') as f:
        user_features = list(csv.reader(f))[0]
    item_vecs = genfromtxt('datasets/content_item_vecs.csv', delimiter=',')
    movie_dict = defaultdict(dict)
    count = 0
    with open('datasets/content_movie_list.csv', newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=',', quotechar='"')
        for line in reader:
            if count == 0:
                count += 1
            else:
                count += 1
                movie_id = int(line[0])
                movie_dict[movie_id]['title'] = line[1]
                movie_dict[movie_id]['genres'] = line[2]
    with open('datasets/content_user_to_genre.pickle', 'rb') as f:
        user_to_genre = pickle.load(f)
    return (item_train, user_train, y_train, item_features, user_features, item_vecs, movie_dict, user_to_genre)


def pprint_train(x_train, features, vs, u_s, maxcount=5, user=True):
    if user:
        flist = ['.0f', '.0f', '.1f', '.1f', '.1f', '.1f', '.1f', '.1f', '.1f', '.1f', '.1f', '.1f', '.1f', '.1f',
                 '.1f', '.1f', '.1f']
    else:
        flist = ['.0f', '.0f', '.1f', '.0f', '.0f', '.0f', '.0f', '.0f', '.0f', '.0f', '.0f', '.0f', '.0f', '.0f',
                 '.0f', '.0f', '.0f']
    head = features[:vs]
    if vs < u_s: print('error, vector start {vs} should be greater then user start {u_s}')
    for i in range(u_s):
        head[i] = '[' + head[i] + ']'
    genres = features[vs:]
    hdr = head + genres
    disp = [split_str(hdr, 5)]
    count = 0
    for i in range(0, x_train.shape[0]):
        if count == maxcount: break
        count += 1
        disp.append([x_train[i, 0].astype(int), x_train[i, 1].astype(int), x_train[i, 2].astype(float),
                     *x_train[i, 3:].astype(float)])
    table = tabulate.tabulate(disp, tablefmt='html', headers='firstrow', floatfmt=flist, numalign='center')
    return table


def split_str(ifeatures, smax):
    ofeatures = []
    for s in ifeatures:
        if not ' ' in s:
            if len(s) > smax:
                mid = int(len(s) / 2)
                s = s[:mid] + ' ' + s[mid:]
        ofeatures.append(s)
    return ofeatures


def print_pred_movies(y_p, item, movie_dict, maxcount=10):
    count = 0
    disp = [['y_p', 'movie id', 'rating ave', 'title', 'genres']]
    for i in range(0, y_p.shape[0]):
        if count == maxcount:
            break
        count += 1
        movie_id = item[i, 0].astype(int)
        disp.append([np.around(y_p[i, 0], 1), item[i, 0].astype(int), np.around(item[i, 2].astype(float), 1),
                     movie_dict[movie_id]['title'], movie_dict[movie_id]['genres']])
    table = tabulate.tabulate(disp, tablefmt='html', headers='firstrow')
    return table


def gen_user_vecs(user_vec, num_items):
    user_vecs = np.tile(user_vec, (num_items, 1))
    return user_vecs


def predict_uservec(user_vecs, item_vecs, model, u_s, i_s, scaler):
    y_p = model.predict([user_vecs[:, u_s:], item_vecs[:, i_s:]])
    y_pu = scaler.inverse_transform(y_p)
    if np.any(y_pu < 0):
        print('Error, expected all positive predictions')
    sorted_index = np.argsort(-y_pu, axis=0).reshape(-1).tolist()  # negate to get largest rating first
    sorted_ypu = y_pu[sorted_index]
    sorted_items = item_vecs[sorted_index]
    sorted_user = user_vecs[sorted_index]
    return (sorted_index, sorted_ypu, sorted_items, sorted_user)


def get_user_vecs(user_id, user_train, item_vecs, user_to_genre):
    if not user_id in user_to_genre:
        print('error: unknown user id')
        return None
    else:
        user_vec_found = False
        for i in range(len(user_train)):
            if user_train[i, 0] == user_id:
                user_vec = user_train[i]
                user_vec_found = True
                break
        if not user_vec_found:
            print('error in get_user_vecs, did not find uid in user_train')
        num_items = len(item_vecs)
        user_vecs = np.tile(user_vec, (num_items, 1))
        y = np.zeros(num_items)
        for i in range(num_items):
            movie_id = item_vecs[i, 0]
            if movie_id in user_to_genre[user_id]['movies']:
                rating = user_to_genre[user_id]['movies'][movie_id]
            else:
                rating = 0
            y[i] = rating
    return (user_vecs, y)


def get_item_genres(item_gvec, genre_features):
    offsets = np.nonzero(item_gvec)[0]
    genres = [genre_features[i] for i in offsets]
    return genres


def print_existing_user(y_p, y, user, items, ivs, uvs, movie_dict, maxcount=10):
    count = 0
    disp = [['y_p', 'y', 'user', 'user genre ave', 'movie rating ave', 'movie id', 'title', 'genres']]
    count = 0
    for i in range(0, y.shape[0]):
        if y[i, 0] != 0:
            if count == maxcount:
                break
            count += 1
            movie_id = items[i, 0].astype(int)
            offsets = np.nonzero(items[i, ivs:] == 1)[0]
            genre_ratings = user[i, uvs + offsets]
            disp.append([y_p[i, 0], y[i, 0], user[i, 0].astype(int),
                         np.array2string(genre_ratings, formatter={'float_kind': lambda x: '%.1f' % x}, separator=',',
                                         suppress_small=True), items[i, 2].astype(float), movie_id,
                         movie_dict[movie_id]['title'], movie_dict[movie_id]['genres']])
    table = tabulate.tabulate(disp, tablefmt='html', headers='firstrow', floatfmt=['.1f', '.1f', '.0f', '.2f', '.1f'])
    return table