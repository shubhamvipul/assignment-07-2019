a = open('../data/json_text.txt')
a = a.readline()
b = a.split('},{')

if len(b)<=5000:
	per_thread = 100
elif len(b)<100000:
	per_thread = 1000
else:
	per_thread = 10000

for ii in range(0,len(b),per_thread):
	fw = open("../newdata/sample"+str(int(ii/per_thread))+".txt","w")
	wtext = '{'+'}\n{'.join(b[ii:ii+per_thread])+'}'
	if ii == 0:
		wtext = wtext[1:]
	elif ii == len(b) - per_thread:
		wtext = wtext[:-1]
	fw.write(wtext)

fw = open("./temp.txt","w")
fw.write(str(int((ii+per_thread)/per_thread)))
fw.close()