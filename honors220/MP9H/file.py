file_in = open("output", 'r')

i = 100
while(i > 0):
    name = "output" + str(i)
    file_out = open(name, 'w')
    file_out.write(file_in.readline(i))
    i = i-1
    file_out.write(file_in.readline(i))
    i = i-1
    file_out.close()
