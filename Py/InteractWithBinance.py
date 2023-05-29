import logging
import requests
import pprint

logger = logging.getLogger()

def get_contracts():
    response_object = requests.get("https://fapi.binance.com/fapi/v1/exchangeInfo")
    print(response_object.status_code)
    pprint.pprint(response_object.json())

get_contracts()