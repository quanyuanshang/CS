import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import random
from matplotlib import font_manager
my_font=font_manager.FontProperties(fname="C:\Windows\Fonts\msyh.ttc")
y=[random.randint(20,25) for i in range(120)]
x=range(120)
plt.figure(figsize=(10,6))
plt.plot(x,y)
_x=list(x)
_xticks=["10点{}分".format(i) for i in range(60)]
_xticks+=["11点{}分".format(i) for i in range(60)]
plt.xticks(_x[::3],_xticks[::3],rotation=45,fontproperties=my_font)
plt.yticks(range(min(y),max(y)+1))
plt.show()
