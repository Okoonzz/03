#Tính năm nhuận 
year = 2024 
if (((year %4 == 0) and (year %100 != 0)) or (year %400 == 0)):
	print ("Năm ",year, " là năm nhuận")
else:
	print ("Năm ", year, " không là năm nhuận") 


