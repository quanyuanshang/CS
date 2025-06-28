from builtins import range
import numpy as np
from random import shuffle
from past.builtins import xrange
# we should download the 'past' module by 'pip install future' ????!!!!

def svm_loss_naive(W, X, y, reg):
    """
    Structured SVM loss function, naive implementation (with loops).

    Inputs have dimension D, there are C classes, and we operate on minibatches
    of N examples.

    Inputs:
    - W: A numpy array of shape (D, C) containing weights.
    - X: A numpy array of shape (N, D) containing a minibatch of data.
    - y: A numpy array of shape (N,) containing training labels; y[i] = c means
        that X[i] has label c, where 0 <= c < C.
    - reg: (float) regularization strength

    Returns a tuple of:
    - loss as single float
    - gradient with respect to weights W; an array of same shape as W
    """

    loss = 0.0
    dW = np.zeros(W.shape) # initialize the gradient as zero

    #############################################################################
    # TODO:                                                                     #
    # Compute the gradient of the loss function and store it dW.                #
    # Rather than first computing the loss and then computing the derivative,   #
    # it may be simpler to compute the derivative at the same time that the     #
    # loss is being computed. As a result you may need to modify some of the    #
    # code above to compute the gradient.                                       #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    num_classes=W.shape[1]
    num_train=X.shape[0]
    for i in range(num_train):
        scores=X[i]@W
        correct_class_score=scores[y[i]]
        for j in range (num_classes):
            if j==y[i]:#不去考虑正确类别，而失去调整其他错误类别，拉开与正确类别的差距
                continue
            margin=scores[j]-correct_class_score+1
            if margin>0:
                loss+=margin
                dW[:,j]+=X[i]
                dW[:,y[i]]-=X[i]#拉开差距,梯度更新w-=dw
    loss/=num_train
    dW/=num_train
    loss+=0.5*reg*np.sum(W*W)
    dW+=reg*W

    pass

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW

def svm_loss_vectorized(W, X, y, reg):
    """
    Structured SVM loss function, vectorized implementation.

    Inputs and outputs are the same as svm_loss_naive.
    """
    loss = 0.0
    dW = np.zeros(W.shape) # initialize the gradient as zero

    #############################################################################
    # TODO:                                                                     #
    # Implement a vectorized version of the structured SVM loss, storing the    #
    # result in loss.                                                           #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    #num_classes=W.shape[1]
    num_train=X.shape[0]
    scores=X@W
    correct_class_scores=scores[np.arange(num_train),y]
    margins=np.maximum(0,scores-correct_class_scores[:,np.newaxis]+1)#使用 [:, np.newaxis] 后，correct_class_scores.shape 变成 (N, 1)
    margins[np.arange(num_train),y]=0
    loss=np.sum(margins)/num_train+0.5*reg*np.sum(W*W)
    


    pass

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    #############################################################################
    # TODO:                                                                     #
    # Implement a vectorized version of the gradient for the structured SVM     #
    # loss, storing the result in dW.                                           #
    #                                                                           #
    # Hint: Instead of computing the gradient from scratch, it may be easier    #
    # to reuse some of the intermediate values that you used to compute the     #
    # loss.                                                                     #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    margins[margins > 0] = 1  # 只保留 margin > 0 的部分
    row_sum = np.sum(margins, axis=1)  # 计算每个样本有多少个 margin > 0
    margins[np.arange(num_train), y] -= row_sum  # 每次其他的类别值有问题也需要调整dW[:,y[i]]-=X[i]
    dW=np.dot(X.T,margins)/num_train+reg*W
    pass

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW
