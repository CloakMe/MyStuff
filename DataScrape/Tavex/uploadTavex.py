from pcloud import PyCloud

def pcloudUpload():
    paro = read_string_from_file('1')
    # Authenticate with your pCloud account
    pc = PyCloud('angelow@protonmail.com', paro)

    target_directory = '/Datascrape/Tavex'  # Target directory in pCloud

    # Call listfolder with the specified path
    response = pc.listfolder(path=target_directory)

    # Check if the request was successful
    if response['result'] == 0:
        # Now setup the upload file
        local_file_path = ['austrian-ducat-gold-coin.txt', 'french-20francs-marianne.txt'] #E:\MyStuff\datascrape\tavex\
        # Extract folder ID from the response
        folder_id = response['metadata']['folderid']
        print(f"Folder ID for '{target_directory}' is: {folder_id}")
        upload_response = pc.uploadfile(files=local_file_path, folderid=folder_id)
        if upload_response['result'] == 0:
            print("File uploaded successfully!")
        else:
            print("Error uploading file:", upload_response['error'])
    else:
        print("Error retrieving folder ID:", response['error'])
    


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
