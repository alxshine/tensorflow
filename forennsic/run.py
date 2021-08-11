import tensorflow as tf
import numpy as np

with tf.device("/device:CPU:0"):
  model = tf.keras.models.load_model("forennsic/minimal.h5")
  sample = np.load("forennsic/sample.npy")

  predictions = model(sample)
  print(predictions)
