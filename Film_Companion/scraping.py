import requests

def get_movie_description(title):
    api_key = "cce0928b"
    api_url = "http://www.omdbapi.com/?apikey=" + api_key + "&t=" + title
    response = requests.get(api_url)
    data = response.json()
    #print(data)
    return data['Plot']

title = "The Shawshank Redemption"
description = get_movie_description(title)
