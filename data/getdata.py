from yahoo_finance import Share
import urllib.request  as urllib2 
from bs4 import BeautifulSoup as bs

def get_historical_data(name,period1,period2):
	data = []

	url = "https://finance.yahoo.com/quote/" + name + "/history?period1="+ str(period1) + "&period2=" + str(period2) + "&interval=1d&filter=history&frequency=1d"
	
	html = urllib2.urlopen(url).read() #Byt ut till längre data

	rows = bs(html).findAll('table')[0].tbody.findAll('tr')

	for each_row in rows:
		divs = each_row.findAll('td')
		if divs[1].span.text  != 'Dividend': #Ignore this row in the table
			#I'm only interested in 'Open' price; For other values, play with divs[1 - 5]
			data.append({'Date': divs[0].span.text, 'Open': float(divs[1].span.text.replace(',',''))})

	return data

#Test
print(get_historical_data('GOOG',1092866400,1509922800))


