import os
import sys
import urllib.request
from time import sleep
import random
import joblib
import numpy as np
from dotenv import load_dotenv
load_dotenv()
# API for upload of data
myurl = os.environ.get("API_TOKEN")

# Simulation of the data from system
while True:
    speed = random.uniform(0, 3)
    governor = 0
    level = random.uniform(-1, 1)
    voltage = random.uniform(100, 260)
    temperature = random.randrange(25, 90)
    emergency = 0

    if speed > 1.8:
        governor += 1
    if temperature > 82:
        emergency = 1

# Preparation for the data for inferernce
    temp = float(temperature)

# Actual Inference
    loaded_model = joblib.load('final_model.sav')
    val = np.array([temp, speed, voltage])
    res = loaded_model.predict(val.reshape(1, -1))
    result = ""
    if (res == 1.0):
        result = "Healthy"
    else:
        result = "Unhealthy"

# Sending the data to the server for visualisation and continuous monitoring
    urllib.request.urlopen(myurl + "&field1=" + str(temperature) + "&field2=" + str(level) + "&field3=" + str(
        speed) + "&field4=" + str(governor) + "&field5=" + str(voltage) + "&field6=" + str(emergency))
    print("Uploaded - The system is " + result)
