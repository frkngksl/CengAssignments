def place_words(Corpus):
	def checker(Corpus,result):
		row_number = len(result)
		column_number = len(result[0])
		slicedlist = []
		if(len(result) == 1):
			return True
		for z in range(0,len(Corpus)):
			if(row_number == column_number):
				slicedlist.append(Corpus[z][:])
			else:
				slicedlist.append(Corpus[z][:row_number])
		kontrol = "" 
		for x in range(0,column_number):
			for y in range(0,row_number):
				kontrol = kontrol + result[y][x]
			if(kontrol not in slicedlist):
				return False
			if(kontrol in result):
				return False
			kontrol = ""
		else:
			return True
	def place(n,corpus,result,row_sayisi):
		if(n > row_sayisi-1):
			return True
		m = 0
		while m < len(corpus):
			result.append(corpus[m])
			if(checker(corpus,result) and place(n+1,corpus,result,row_sayisi)):
				return result
			else:
				del result[-1]
				m= m+1 
		return False
	newCorpus = []
	result = []
	if(len(Corpus) == 0):
		return False
	N = len(Corpus[0]) #Row sayisi
	for i in range(0,len(Corpus)):
		newCorpus.append(Corpus[i].upper())
	if(N == 1):
		return False
	return place(0,newCorpus,result,N)
	
		
		

