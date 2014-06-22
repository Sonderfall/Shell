#!/Applications/Python
# -*-coding:utf-8 -*

import os
import subprocess
import sys
import signal

from subprocess import Popen, PIPE, STDOUT

directories = os.getcwd() + "/test_suite/"
# We go in the 'test_suite' directory, where all the categories of tests are

test   = 1
tok    = 0


class TimeoutException(Exception):
	pass

def filtre(source, destination):
	fs = open(source, 'r')
	fd = open(destination, 'w')
	while 1:
		txt = fs.readline()
		if txt == '':
			break
		if txt[0] != '#':
			fd.write(txt)
	fs.close()
	fd.close()
	return

def printest(i, category):
	strc = " test (" + category + ")"
	if (i % 10 == 1 and i % 100 != 11):
		strc = "st" + strc
	elif (i % 10 == 2 and i % 100 != 12):
		strc = "nd" + strc
	elif (i % 10 == 3 and i % 100 != 13):
		strc = "rd" + strc
	else:
		strc = "th" + strc
	i = str(i)
	strc = i + strc
	i = int(i)
	if (i < 100):
		strc = " " + strc
	if (i < 10):
		strc = " " + strc
	return (strc)

def printescape(i, tok):
	strc = ""
	if (tok < 1):
		strc += " "
	if (i < 100):
		strc += " "
		if (i < 10):
			strc += " "
	if (tok < 99):
		strc += " "
		if (tok < 9):
			strc += " "
	return (strc)

def diff(category, bash, shsh, i, tok, cat, sel, fin, num, al):
	if (bash == shsh):
		strc2 = printescape(i, tok) + " \033[1;32mOK\033[0;37m"
		tok += 1
	else:
		#if (statusbash != status42 and outputbash == output42):
		#	strc2 = " \033[1;31mKO \033[0;31m(bad status)\033[0;37m"
		#elif (statusbash == status42 and outputbash != output42):
		#	strc2 = " \033[1;31mKO \033[0;31m(bad output)\033[0;37m"
		#else:
		#	strc2 = " \033[1;31mKO \033[0;31m(bad status & bad output)\033[0;37m"
		strc2 = printescape(i, tok) + " \033[1;31mKO \033[0;31m(bad status/output)\033[0;37m"
	i2   = str(i)
	tok2 = str(tok)
	strc = printest(i, category) + " (" + tok2 + "/" + i2 + " successfull test"
	if (tok > 1):
		strc += "s"
	strc += "):" + strc2
	if (cat == 0):
		print(strc)
	return (tok)

def manage(category, data, i, tok, timout, cat, sel, fin, num, al):
	def timeout_handler(signum, frame):
		raise TimeoutException()

	data = data[:-1]

	old_handler = signal.signal(signal.SIGALRM, timeout_handler)
	try:
		if (timout < 1):
			signal.alarm(2)
		else:
			timt = int(round(float(timout), 0))
			signal.alarm(timt)
	except ValueError:
		signal.alarm(2)

	try:
		data2 = "bash -c " + data
		#statusbash, outputbash = commands.getstatusoutput(data2)	
		p = Popen(data2, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
    bash = p.communicate()
	except TimeoutException:
		p.kill()
		i2   = str(i)
		tok2 = str(tok)
		str1 = printest(i, category) + " ("
		str1 += tok2 + "/" + i2 + " successfull test"
		if (tok > 1):
			str1 += "s"
		str1 += "):" + printescape(i, tok) + " \033[1;31mKO\033[0;31m (timeout on bash)\033[0;37m"
		if (cat == 0 and num == 0 and fin == 0):
			print (str1)
		signal.alarm(0)
		p.kill()
		return (tok)
	finally:
		signal.signal(signal.SIGALRM, old_handler)

	try:
		data2 = "zsh -c " + data
		p = Popen(data2, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
		shsh = p.communicate()
	except TimeoutException:
		p.kill()
		i2   = str(i)
		tok2 = str(tok)
		str2 = printest(i, category) + " ("
		str2 += tok2 + "/" + i2 + " successfull test"
		if (tok > 1):
			str2 += "s"
		str2 += "):" + printescape(i, tok) + " \033[1;31mKO\033[0;31m (timeout on 42sh)\033[0;37m" 
		if (cat == 0 and fin == 0 and num == 0):
			print (str2)
		signal.alarm(0)
		p.kill()
		return (tok)
	finally:
		signal.signal(signal.SIGALRM, old_handler)

	signal.alarm(0)
	return (diff(category, bash, shsh, i, tok, cat, sel, fin, num, al))

def main(directories, test, tok):
	cat = 0
	sel = 0
	fin = 0
	num = 0
	tim = -1
	al = 0
	if (len(sys.argv) == 1):
		al = 1
	else:
		acc = 1
		while (acc < len(sys.argv)):
			if (sys.argv[acc] == "-c" or sys.argv[acc] == "-categories"):
				cat = 1
				acc += 1
				continue
			elif (sys.argv[acc] == "-f" or sys.argv[acc] == "-final"):
				fin = 1
				cat = 1
				acc += 1
				continue
			elif (sys.argv[acc] == "-n" or sys.argv[acc] == "-number"):
				num = 1
				cat = 1
				acc += 1
				continue
			elif (sys.argv[acc] == "-e" or sys.argv[acc] == "-select"):
				sel = 1
				acc += 1	
				continue
			elif (sys.argv[acc] == "-t" or sys.argv[acc] == "-timeout"):
				acc += 1	
				tim = sys.argv[acc]
				acc += 1
				continue
			elif (sys.argv[acc] == "-a" or sys.argv[acc] == "-all"):
				al = 1
				acc += 1
				continue
			else:
				acc += 1
				continue
			
	test3 = 0
	tok3  = 0
	for category in os.listdir(directories):
		# We go in all categories
		catsel = 0
		if (sel != 0):
			acc = 1
			while (acc < len(sys.argv)):
				if (sys.argv[acc] == "-e" or sys.argv[acc] ==  "-select"):
					acc += 1
					while (acc < len(sys.argv)):
						if (category == sys.argv[acc]):
							catsel = 1
						elif (sys.argv[acc][0] == "-"):
							acc = len(sys.argv)
						acc += 1
				else:
					acc += 1
						
			if (catsel == 0):
				continue
		test = 1
		tok  = 0
		actualcategory = directories + category
		for fichier in os.listdir(actualcategory):
			# We launch on all the file in the category'
			file = os.path.join(actualcategory, fichier)
			if os.path.isfile(file):
				dat  = open(file, 'r')
				data = dat.read()
				if (data != ""):
					tok = manage(category, data, test, tok, tim, cat, sel, fin, num, al)
					# We call the function on the string in the file test
					test += 1
				dat.close()
		test -= 1
		test3 += test
		tok3  += tok
		tok2   = str(tok)
		test2  = str(test)
		if (test != 0):
			percen = (100 * tok) / test
		else:
			percen = 100
		perce2 = str(percen)
		
		if (fin == 0 and num == 0):
			strcat = tok2 + " / " + test2 + " successful tests in the category '" + category + "' (" + perce2 + "%)"
			if (cat == 0):
				strcat += "\n"
			print(strcat)	
	tok4   = str(tok3)
	test4  = str(test3)
	if (test3 != 0):
		percen = (100 * tok3) / test3
	else:
		percen = 100
	perce2 = str(percen)
	if ((fin == 0 and num == 0) or (fin != 0 and num != 0)):
		strcat = "\n" + tok4 + " / " + test4 + " successful tests on all categories (" + perce2 + "%)\n"
	if (fin == 0 and num != 0):
		strcat = "\n" + tok4 + " / " + test4 + " successful tests on all categories\n"
	if (fin != 0 and num == 0):
		strcat = "\n" + perce2 + "% of successful tests on all categories\n"
	print(strcat)


main(directories, test, tok)
