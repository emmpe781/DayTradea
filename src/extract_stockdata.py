from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import Select
from selenium.webdriver.common.keys import Keys

# Create a new instance of the Chrome driver
driver = webdriver.Chrome('chromedriver.exe')
# go to the google home page
driver.get("http://www.nasdaqomxnordic.com/aktier/historiskakurser") 

inputElement = driver.find_element_by_name("instSearchHistorical")
inputElement.send_keys("Bure Equity")
dropdown = driver.find_element_by_id('ui-id-2')
#dropdown.send_keys(Keys.ARROW_DOWN) # tab over to not-visible element



#
#dropdown = driver.find_element_by_id("ui-id-2")
#dropdown.send_keys(Keys.DOWN);

#inputElement.send_keys(Keys.ENTER);

#
#

# type in the search
#new Select().selectByVisibleText("Germany");

# submit the form (although google automatically searches now without submitting)
#

# the page is ajaxy so the title is originally this:
print(driver.title)

try:
    # we have to wait for the page to refresh, the last thing that seems to be updated is the title
    WebDriverWait(driver, 10).until(EC.title_contains("cheese!"))

    # You should see "cheese! - Google Search"
    print(driver.title)

finally:
    driver.quit()

  #browser.visit('http://www.nasdaqomxnordic.com/aktier/historiskakurser')
  