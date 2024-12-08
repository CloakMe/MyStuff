import requests
from bs4 import BeautifulSoup
from datetime import datetime

def save_gold_coin_price(url, coinName):
    # https://tavex.bg/en/gold/austrian-ducat-gold-coin/
    urlFull = url + coinName
    response = requests.get(urlFull)

    if response.status_code == 200:
        soup = BeautifulSoup(response.text, 'html.parser')

        # Find the price element using the correct class name
        price_info = soup.find('span', class_='product-poster__price-value js-product-price-from')
        
        if price_info:
            price = price_info.text.strip()
            print(f"The price of the French 20 Francs Marianne is: {price}")
            
            # Append the price and timestamp to the file
            append_to_file(coinName, price)
        else:
            print("Price information not found.")
    else:
        print("Failed to retrieve the webpage.")

def append_to_file(fileName, price):
    # Get current date and time
    current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    # Prepare the line to write
    line_to_write = f"{current_time}: {price}\n"
    
    # Open file in append mode, create it if it doesn't exist
    with open(fileName + ".txt", "a") as file:
        file.write(line_to_write)

# Main execution block
if __name__ == "__main__":
    mariana = "french-20francs-marianne"
    austDucat = "austrian-ducat-gold-coin"
    url = "https://tavex.bg/en/gold/"
    save_gold_coin_price(url, mariana)
    save_gold_coin_price(url, austDucat)