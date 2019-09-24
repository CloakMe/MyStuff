import os
import selenium as selen
import time
from selenium import webdriver

driver = webdriver.Chrome("E:\\who\\MyStuff\\python\\WebScraper\\chromedriver_win32\\chromedriver")

driver.maximize_window() #For maximizing window
driver.implicitly_wait(3) #gives an implicit wait for 20 seconds

driver.get('https://www.efbet.com/BG/homepage')
#
# time.sleep(3)
# driver.implicitly_wait(3) //*[@id="EfbetChannelNavigationComponent15-navigation-list"]/li[3]/a
el = driver.find_element_by_xpath('//*[@id="EfbetChannelNavigationComponent15-navigation-list"]/li[3]')
el.click()
# # driver.implicitly_wait(3)
# el = driver.find_element_by_xpath('//*[@id="index-container"]')

iframe = driver.find_element_by_xpath('//*[@id="virtualsAppMain"]')
driver.switch_to.frame(iframe)


# time.sleep(3)
iframe = driver.find_element_by_xpath('//*[@id="vfl_iframe"]')
driver.switch_to.frame(iframe)

el_stat = driver.find_element_by_xpath('//*[@id="statistik"]')
el_stat.click()

time.sleep(3)
driver.switch_to.window(driver.window_handles[1])


el = driver.find_element_by_xpath('//*[@id="node_main-wrap"]/div[5]/div[1]/div/div/div[2]/div/div/div[1]/div[1]/div[1]/div/div/div[1]/div/div[2]')
el.click()

# driver.get('https://www.amazon.de/gp/bestsellers/?ref_=nav_cs_bestsellers')
# el = driver.find_element_by_xpath( '//*[@id="zg_left_col1"]/div[1]/div[2]/div/div[2]/a/div[1]/img' )
# //*[@id="node_main-wrap"]/div[5]/div[1]/div/div/div[2]/div/div/div[1]/div[1]/div[1]/div/div/div[3]/div[2]/ul/li

driver.maximize_window() #For maximizing window
driver.implicitly_wait(3) #gives an implicit wait for 20 seconds

xpath = '//*[@id="node_main-wrap"]/div[5]/div[1]/div/div/div[2]/div/div/div[1]/div[1]/div[1]/div/div/div[3]/div[2]/ul/li'
elems_li = driver.find_elements_by_xpath(xpath)



elems_li[2].click()


