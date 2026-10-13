from pathlib import Path
import requests
import json
import sys

def read_string_from_file(filename):
    """
    Reads a single string from a file and returns it.

    Parameters:
    filename (str): The name of the file to read.

    Returns:
    str: The string read from the file.
    """
    try:
        with open(filename, 'r') as file:
            # Read the content of the file
            content = file.read().strip()  # Use strip() to remove any leading/trailing whitespace
            return content
    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None
        
def load_token():
    p_map_as_str = read_string_from_file('1')
    return json.loads(p_map_as_str)
    
def pcloudUpload():
    remote_folder = "/Datascrape/Tavex"      # must already exist
    local_files = ['austrian-ducat-gold-coin.txt', 'french-20francs-marianne.txt']
    headers, params = {}, {"path": remote_folder, "nopartial": 1}
    token = load_token()
    if token["kind"] == "oauth":
        headers["Authorization"] = f"Bearer {token['value']}"
    else:
        params["auth"] = token["value"]

    for name in local_files:
        try:
            with open(name, "rb") as f:
                r = requests.post(
                    f"https://{token['host']}/uploadfile",
                    params=params, headers=headers,
                    files={"file": (Path(name).name, f)},
                    timeout=300,
                )
            data = r.json()
            if data.get("result") != 0:
                print(f"Failed {name}: {data.get('result')} {data.get('error')}")
            else:
                print("Upload complete:", data["metadata"][0]["name"])
        except (OSError, requests.RequestException) as e:
            print(f"Failed {name}: {e}")



