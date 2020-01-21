with open("mp11.c" , 'r') as text:
    count = text.readlines()

counter= 0

for line in count:
    if "/*" in line or "{" in line:
        continue
    counter+=1    

print counter
