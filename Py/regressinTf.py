import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()

#create data set
x = np.linspace(0.0, 10.0, 1000000)
y = (0.7 * x) + 8 + np.random.randn(len(x))
x_df = pd.DataFrame(data=x, columns=['X'])
print(x_df)
y_df = pd.DataFrame(data=y, columns=['Y'])
print(y_df)

collect_data = pd.concat([x_df, y_df], axis=1)
print(collect_data)
collect_data.sample(300).plot(kind='scatter', x='X', y='Y')
#plt.show()
axes = plt.gca()
axes.set_xlim(0,20)
axes.set_xlim(0,10)
line, = axes.plot(x_df, y_df, 'r-')

#create model
step_size=10
m = tf.Variable(0.21)
b = tf.Variable(0.71)
x_ph = tf.placeholder(tf.float32)
y_ph = tf.placeholder(tf.float32)
model_eq = tf.add(tf.multiply(m, x_ph),b) #model_eq = m*x_ph+b
train_model = tf.train.GradientDescentOptimizer(learning_rate=1e-5).minimize(tf.reduce_mean(tf.square((y_ph)-model_eq)))
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    train_step = 1000000
    for i in range(train_step):
        index = np.random.randint(len(x),size=step_size)
        feed = {x_ph: x[index], y_ph:y[index]}
        sess.run(train_model, feed_dict=feed)
        #mode_m, model_b = sess.run([m,b])
        result_m, result_b = sess.run([m, b])
        result_y = x * result_m + result_b
        line.set_xdata(x)
        line.set_ydata(result_y)
        plt.draw()
        plt.pause(1e-20)

result_y = x * result_m + result_b
plt.plot(x, result_y, 'r')
plt.show()
