def minority_shape_intersect(firstshape,secondshape):
	def insidetheshape(a,b,c,d):
		bx = b[0] - a[0]
		by = b[1] - a[1]
		cx = c[0] - a[0]
		cy = c[1] - a[1]
		x = d[0] - a[0]
		y = d[1] - a[1]	
		z = float((bx*cy)) - float((cx*by))        
		Wa = (x*(by-cy)+y*(cx-bx)+bx*cy-cx*by)/z
		Wb = ((x*cy)-(y*cx))/z
		Wc = ((y*bx-x*by))/z
		if(0<=Wa<=1 and 0<=Wb<=1 and 0<=Wc<=1):
			result = [d]
			return result
	def isequal(liste):
		i=0
		j=0
		last = len(liste)
		reference = 0.0000000001
		while i < last:
			while j < last:
				if( i != j):
					if(abs(liste[i][0]-liste[j][0]) < reference and abs(liste[i][1]-liste[j][1]) < reference):
						del liste[i]
				j+=1
			i+=1
		return liste

	def interactionpoint3v3(x0,x1,y0,y1):
		dy1 = float(x0[1]) - float(x1[1])
		dx1 = float(x0[0]) - float(x1[0])
		dy2 = float(y0[1]) - float(y1[1])
		dx2 = float(y0[0]) - float(y1[0])
		if(abs(dx1) < 0.001 and abs(dx2) < 0.001):
			return 0	
		elif(abs(dx1) < 0.001):
			kesisimnoktasix = x0[0]
			slope2 = dy2/dx2
			n2= float(y0[1])-(slope2)*(float(y0[0]))
			kesisimnoktasiy = (slope2)*x0[0]+n2
		elif(abs(dx2) < 0.001):
			kesisimnoktasix = y0[0]
			slope1=dy1/dx1
			n1= float(x0[1])-(slope1)*(float(x0[0]))
			kesisimnoktasiy = (slope1)*y0[0]+n1	
		else:
	        	slope1 = dy1/dx1
			n1= float(x0[1])-(slope1)*(float(x0[0]))
			slope2 = dy2/dx2
			n2= float(y0[1])-(slope2)*(float(y0[0]))
			if(abs(slope1-slope2) < 0.001):
				return 0 
			kesisimnoktasix = (n2-n1)/(slope1-slope2)
			kesisimnoktasiy = slope1*kesisimnoktasix + n1
		if(x0[0] > x1[0]):
			maxx1=x0[0]
			minx1=x1[0]
		else:
			maxx1=x1[0]
			minx1=x0[0]
		if(x0[1] > x1[1]):
			maxy1=x0[1]
			miny1=x1[1]
		else:
			maxy1=x1[1]
			miny1=x0[1]
		if(y0[0] > y1[0]):
			maxx2=y0[0]
			minx2=y1[0]
		else:
			maxx2=y1[0]
			minx2=y0[0]
		if(y0[1] > y1[1]):
			maxy2=y0[1]
			miny2=y1[1]
		else:
			maxy2=y1[1]
			miny2=y0[1]
		if(maxx1 >= kesisimnoktasix >= minx1 and maxx2 >= kesisimnoktasix >= minx2 and maxy1 >= kesisimnoktasiy >= miny1 and maxy2 >= kesisimnoktasiy >= miny2):
			result = [(kesisimnoktasix,kesisimnoktasiy)] 
			return result
	result = []
	if(len(firstshape) == 3 and len(secondshape) == 3): #ucgen vs ucgen
		if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[0])):
			if(secondshape[0] not in result):		
				result.append(secondshape[0])
		if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[1])):
			if(secondshape[1] not in result):		
				result.append(secondshape[1])
		if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[2])):
			if(secondshape[2] not in result):		
				result.append(secondshape[2])
		if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[0])):
			if(firstshape[0] not in result):		
				result.append(firstshape[0])
		if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[1])):
			if(firstshape[1] not in result):		
				result.append(firstshape[1])
		if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[2])):
			if(firstshape[2] not in result):		
				result.append(firstshape[2])
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1]))
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[2])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[2]))
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1]))
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[2])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[2]))
		if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[1]))
		if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[2])):
			if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[2]))
		if(len(result) == 2 or len(result) == 1):
			result = []	
		result = isequal(result)
		return result
	if(len(firstshape) == 3 and len(secondshape) == 4): # ucgen vs dortgen
		if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[0])):
			if(secondshape[0] not in result):
				result.append(secondshape[0])
		if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[1])):
			if(secondshape[1] not in result):
				result.append(secondshape[1])
		if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[2])):
			if(secondshape[2] not in result):
				result.append(secondshape[2])
		if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[3])):
			if(secondshape[3] not in result):
				result.append(secondshape[3]) 
		if(insidetheshape(secondshape[1],secondshape[2],secondshape[3],secondshape[0]) or insidetheshape(secondshape[0],secondshape[1],secondshape[3],secondshape[2])):
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[0]) or insidetheshape(secondshape[0],secondshape[2],secondshape[3],firstshape[0])):
				if(firstshape[0] not in result):		
					result.append(firstshape[0])	
		else:
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[3],firstshape[0]) or insidetheshape(secondshape[1],secondshape[2],secondshape[3],firstshape[0])):
				if(firstshape[0] not in result):		
					result.append(firstshape[0]) 
		if(insidetheshape(secondshape[1],secondshape[2],secondshape[3],secondshape[0]) or insidetheshape(secondshape[0],secondshape[1],secondshape[3],secondshape[2])):
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[1]) or insidetheshape(secondshape[0],secondshape[2],secondshape[3],firstshape[1])):
				if(firstshape[1] not in result):		
					result.append(firstshape[1])	
		else:
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[3],firstshape[1]) or insidetheshape(secondshape[1],secondshape[2],secondshape[3],firstshape[1])):
				if(firstshape[1] not in result):		
					result.append(firstshape[1]) 
		if(insidetheshape(secondshape[1],secondshape[2],secondshape[3],secondshape[0]) or insidetheshape(secondshape[0],secondshape[1],secondshape[3],secondshape[2])):
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[2]) or insidetheshape(secondshape[0],secondshape[2],secondshape[3],firstshape[2])):
				if(firstshape[2] not in result):		
					result.append(firstshape[2])	
		else:
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[3],firstshape[2]) or insidetheshape(secondshape[1],secondshape[2],secondshape[3],firstshape[2])):
				if(firstshape[2] not in result):		
					result.append(firstshape[2]) #iceride olma durumu sonu
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1]))	
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[2],secondshape[3])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[2],secondshape[3])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[2],secondshape[3]))
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[3],secondshape[0])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[3],secondshape[0])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[3],secondshape[0])) 
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1]))	
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[2],secondshape[3])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[2],secondshape[3])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[2],secondshape[3])) 
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[3],secondshape[0])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[3],secondshape[0])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[3],secondshape[0])) 
		if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[0],secondshape[1]))	
		if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[2],secondshape[3])):
			if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[2],secondshape[3])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[2],secondshape[3]))
		if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[3],secondshape[0])):
			if(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[3],secondshape[0])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[2],secondshape[3],secondshape[0])) #3.kenar sonu
		if(len(result) == 2 or len(result) == 1):
			result = []
		result = isequallikbulma(result)
		return result
	if(len(firstshape) == 4 and len(secondshape) == 3): #dortgen vs ucgen
		if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[0])):
			if(firstshape[0] not in result):		
				result.append(firstshape[0])
		if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[1])):
			if(firstshape[1] not in result):		
				result.append(firstshape[1])
		if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[2])):
			if(firstshape[2] not in result):		
				result.append(firstshape[2])
		if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[3])):
			if(firstshape[3] not in result):		
				result.append(firstshape[3]) 
		if(insidetheshape(firstshape[1],firstshape[2],firstshape[3],firstshape[0]) or insidetheshape(firstshape[0],firstshape[1],firstshape[3],firstshape[2])):
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[0]) or insidetheshape(firstshape[0],firstshape[2],firstshape[3],secondshape[0])):
				if(secondshape[0] not in result):		
					result.append(secondshape[0])	
		else:
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[3],secondshape[0]) or insidetheshape(firstshape[1],firstshape[2],firstshape[3],secondshape[0])):
				if(secondshape[0] not in result):		
					result.append(secondshape[0])	
		if(insidetheshape(firstshape[1],firstshape[2],firstshape[3],firstshape[0]) or insidetheshape(firstshape[0],firstshape[1],firstshape[3],firstshape[2])):
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[1]) or insidetheshape(firstshape[0],firstshape[2],firstshape[3],secondshape[1])):
				if(secondshape[1] not in result):		
					result.append(secondshape[1])	
		else:
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[3],secondshape[1]) or insidetheshape(firstshape[1],firstshape[2],firstshape[3],secondshape[1])):
				if(secondshape[1] not in result):		
					result.append(secondshape[1])	
		if(insidetheshape(firstshape[1],firstshape[2],firstshape[3],firstshape[0]) or insidetheshape(firstshape[0],firstshape[1],firstshape[3],firstshape[2])):
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[2]) or insidetheshape(firstshape[0],firstshape[2],firstshape[3],secondshape[2])):
				if(secondshape[2] not in result):		
					result.append(secondshape[2])	
		else:
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[3],secondshape[2]) or insidetheshape(firstshape[1],firstshape[2],firstshape[3],secondshape[2])):
				if(secondshape[2] not in result):		
					result.append(secondshape[2])	 #iceride olma durumu sonu
		if(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[0],firstshape[1])):
			if(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[0],firstshape[1])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[0],firstshape[1]))	
		if(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[1],firstshape[2])):
			if(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[1],firstshape[2])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[1],firstshape[2]))
		if(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[2],firstshape[3])):
			if(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[2],firstshape[3])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[2],firstshape[3]))
		if(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[3],firstshape[0])):
			if(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[3],firstshape[0])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[0],secondshape[1],firstshape[3],firstshape[0])) 
		if(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[0],firstshape[1])):
			if(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[0],firstshape[1])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[0],firstshape[1]))	
		if(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[1],firstshape[2])):
			if(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[1],firstshape[2])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[1],firstshape[2]))
		if(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[2],firstshape[3])):
			if(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[2],firstshape[3])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[2],firstshape[3])) 
		if(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[3],firstshape[0])):
			if(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[3],firstshape[0])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[1],secondshape[2],firstshape[3],firstshape[0])) 
		if(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[0],firstshape[1])):
			if(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[0],firstshape[1])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[0],firstshape[1]))	
		if(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[1],firstshape[2])):
			if(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[1],firstshape[2])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[1],firstshape[2]))
		if(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[2],firstshape[3])):
			if(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[2],firstshape[3])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[2],firstshape[3]))
		if(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[3],firstshape[0])):
			if(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[3],firstshape[0])[0] not in result):
				result.extend(interactionpoint3v3(secondshape[0],secondshape[2],firstshape[3],firstshape[0])) #3.kenar sonu
		if(len(result) == 2 or len(result) == 1):
			result = []
		result = isequal(result)
		return result
	if(len(firstshape) == 4 and len(secondshape) == 4):
		if(insidetheshape(firstshape[1],firstshape[2],firstshape[3],firstshape[0]) or insidetheshape(firstshape[0],firstshape[1],firstshape[3],firstshape[2])):
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[0]) or insidetheshape(firstshape[0],firstshape[2],firstshape[3],secondshape[0])):
				if(secondshape[0] not in result):		
					result.append(secondshape[0])	
		else:
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[3],secondshape[0]) or insidetheshape(firstshape[1],firstshape[2],firstshape[3],secondshape[0])):
				if(secondshape[0] not in result):		
					result.append(secondshape[0])	
		if(insidetheshape(firstshape[1],firstshape[2],firstshape[3],firstshape[0]) or insidetheshape(firstshape[0],firstshape[1],firstshape[3],firstshape[2])):
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[1]) or insidetheshape(firstshape[0],firstshape[2],firstshape[3],secondshape[1])):
				if(secondshape[1] not in result):		
					result.append(secondshape[1])	
		else:
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[3],secondshape[1]) or insidetheshape(firstshape[1],firstshape[2],firstshape[3],secondshape[1])):
				if(secondshape[1] not in result):		
					result.append(secondshape[1])		
		if(insidetheshape(firstshape[1],firstshape[2],firstshape[3],firstshape[0]) or insidetheshape(firstshape[0],firstshape[1],firstshape[3],firstshape[2])):
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[2]) or insidetheshape(firstshape[0],firstshape[2],firstshape[3],secondshape[2])):
				if(secondshape[2] not in result):		
					result.append(secondshape[2])	
		else:
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[3],secondshape[2]) or insidetheshape(firstshape[1],firstshape[2],firstshape[3],secondshape[2])):
				if(secondshape[2] not in result):		
					result.append(secondshape[2])		
		if(insidetheshape(firstshape[1],firstshape[2],firstshape[3],firstshape[0]) or insidetheshape(firstshape[0],firstshape[1],firstshape[3],firstshape[2])):
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[2],secondshape[3]) or insidetheshape(firstshape[0],firstshape[2],firstshape[3],secondshape[3])):
				if(secondshape[3] not in result):		
					result.append(secondshape[3])	
		else:
			if(insidetheshape(firstshape[0],firstshape[1],firstshape[3],secondshape[3]) or insidetheshape(firstshape[1],firstshape[2],firstshape[3],secondshape[3])):
				if(secondshape[3] not in result):		
					result.append(secondshape[3])	#1. sonu				
		if(insidetheshape(secondshape[1],secondshape[2],secondshape[3],secondshape[0]) or insidetheshape(secondshape[0],secondshape[1],secondshape[3],secondshape[2])):
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[0]) or insidetheshape(secondshape[0],secondshape[2],secondshape[3],firstshape[0])):
				if(firstshape[0] not in result):		
					result.append(firstshape[0])	
		else:
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[3],firstshape[0]) or insidetheshape(secondshape[1],secondshape[2],secondshape[3],firstshape[0])):
				if(firstshape[0] not in result):		
					result.append(firstshape[0])		
		if(insidetheshape(secondshape[1],secondshape[2],secondshape[3],secondshape[0]) or insidetheshape(secondshape[0],secondshape[1],secondshape[3],secondshape[2])):
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[1]) or insidetheshape(secondshape[0],secondshape[2],secondshape[3],firstshape[1])):
				if(firstshape[1] not in result):		
					result.append(firstshape[1])	
		else:
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[3],firstshape[1]) or insidetheshape(secondshape[1],secondshape[2],secondshape[3],firstshape[1])):
				if(firstshape[1] not in result):		
					result.append(firstshape[1])		
		if(insidetheshape(secondshape[1],secondshape[2],secondshape[3],secondshape[0]) or insidetheshape(secondshape[0],secondshape[1],secondshape[3],secondshape[2])):
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[2]) or insidetheshape(secondshape[0],secondshape[2],secondshape[3],firstshape[2])):
				if(firstshape[2] not in result):		
					result.append(firstshape[2])	
		else:
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[3],firstshape[2]) or insidetheshape(secondshape[1],secondshape[2],secondshape[3],firstshape[2])):
				if(firstshape[2] not in result):		
					result.append(firstshape[2])		
		if(insidetheshape(secondshape[1],secondshape[2],secondshape[3],secondshape[0]) or insidetheshape(secondshape[0],secondshape[1],secondshape[3],secondshape[2])):
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[2],firstshape[3]) or insidetheshape(secondshape[0],secondshape[2],secondshape[3],firstshape[3])):
				if(firstshape[3] not in result):		
					result.append(firstshape[3])	
		else:
			if(insidetheshape(secondshape[0],secondshape[1],secondshape[3],firstshape[3]) or insidetheshape(secondshape[1],secondshape[2],secondshape[3],firstshape[3])):
				if(firstshape[3] not in result):		
					result.append(firstshape[3])		 #ic ice olma durumu
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[0],secondshape[1]))
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[2],secondshape[3])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[2],secondshape[3])[0] not in result):		
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[2],secondshape[3]))
		if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[3],secondshape[0])):
			if(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[3],secondshape[0])[0] not in result):		
				result.extend(interactionpoint3v3(firstshape[0],firstshape[1],secondshape[3],secondshape[0]))
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[0],secondshape[1]))
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[2],secondshape[3])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[2],secondshape[3])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[2],secondshape[3]))
		if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[3],secondshape[0])):
			if(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[3],secondshape[0])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[1],firstshape[2],secondshape[3],secondshape[0]))
		if(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[0],secondshape[1]))
		if(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[2],secondshape[3])):
			if(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[2],secondshape[3])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[2],secondshape[3]))
		if(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[3],secondshape[0])):
			if(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[3],secondshape[0])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[2],firstshape[3],secondshape[3],secondshape[0]))
		if(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[0],secondshape[1])):
			if(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[0],secondshape[1])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[0],secondshape[1]))
		if(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[1],secondshape[2])):
			if(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[1],secondshape[2])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[1],secondshape[2]))
		if(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[2],secondshape[3])):
			if(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[2],secondshape[3])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[2],secondshape[3]))
		if(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[3],secondshape[0])):
			if(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[3],secondshape[0])[0] not in result):
				result.extend(interactionpoint3v3(firstshape[3],firstshape[0],secondshape[3],secondshape[0]))
		if(len(result) == 2 or len(result) == 1):
			result = []
		result = isequal(result)
		return result
	
""" ANA FORMUL
dy1 = float(firstshape[0][1]) - float(firstshape[1][1])
dx1 = float(firstshape[0][0]) - float(firstshape[1][0])
slope1 = dy1/dx1
n1= float(firstshape[0][1])-(slope1)*(float(firstshape[0][0]))
dy2 = float(secondshape[0][1]) - float(secondshape[1][1])
dx2 = float(secondshape[0][0]) - float(secondshape[1][0])
slope2 = dy2/dx2
n2= float(secondshape[0][1])-(slope2)*(float(secondshape[0][0]))
kesisimnoktasix = (n2-n1)/(slope1-slope2)
kesisimnoktasiy = slope1*kesisimnoktasix + n1
result = [(kesisimnoktasix,kesisimnoktasiy)]  """
