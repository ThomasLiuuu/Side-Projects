# use Long Short Term Memory (LSTM) to predict stock price
import math
import yfinance as yf
import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from tensorflow.python.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM
import matplotlib.pyplot as plt
plt.style.use('fivethirtyeight')

# get stock dataframe
df = yf.download('AAPL', start='2012-01-01', end='2024-06-10')  
print(df.head(10))
print(df.shape)

# visualize closing price
plt.figure(figsize=(16,8))
plt.title('Apple Inc. Close Price History')
plt.plot(df['Close'])
plt.xlabel('Date', fontsize=18)
plt.ylabel('Close Price USD ($)', fontsize=18)
plt.show()

data = df.filter(['Close'])
dataset = data.values
training_data_len = math.ceil(len(dataset) * .8)

# scale data
scalar = MinMaxScaler(feature_range=(0,1))
scaled_data = scalar.fit_transform(dataset)

# train data set
train_data = scaled_data[0:training_data_len, :]
x_train, y_train = [], []

for i in range(60, len(train_data)):
  x_train.append(train_data[i-60:i, 0])
  y_train.append(train_data[i, 0])
  
# convert x_train and y_train to numpy array
x_train, y_train = np.array(x_train), np.array(y_train)
x_train = np.reshape(x_train, (x_train.shape[0], x_train.shape[1], 1))

# build LSTM model
model = Sequential()
model.add(LSTM(50, return_sequences=True, input_shape=(x_train.shape[1], 1)))
model.add(LSTM(50, return_sequences=False))
model.add(Dense(25))
model.add(Dense(1))

# compile model
model.compile(optimizer='adam', loss='mean_squared_error')

# train model
model.fit(x_train, y_train, batch_size=1, epochs=1)

# create test data set
test_data = scaled_data[training_data_len - 60:, :]
x_test, y_test = [], dataset[training_data_len:, :]
for i in range(60, len(test_data)):
  x_test.append(test_data[i-60:i, 0])
  
x_test = np.array(x_test)
x_test = np.reshape(x_test, (x_test.shape[0], x_test.shape[1], 1))

# predict price
prediction = model.predict(x_test)
prediction = scalar.inverse_transform(prediction)

# get root mean squared error
rmse = np.sqrt(np.mean(prediction - y_test) ** 2)

# plot data
train = data[:training_data_len]
valid = data[training_data_len:]
valid['Prediction'] = prediction

# visualize data
plt.figure(figsize=(16,8))
plt.title('Model')
plt.xlabel('Date', fontsize=18)
plt.ylabel('Close Price USD ($)', fontsize=18)
plt.plot(train['Close'])
plt.plot(valid[['Close', 'Prediction']])
plt.legend(['Train', 'Validation', 'Prediction'], loc='lower right')

