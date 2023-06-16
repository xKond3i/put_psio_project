import os

out_h = '--- HEADERS ---\n'
out_cpp = '--- C++ FILES ---\n'

out_h += os.popen('cd "PSiO Team Project" && git ls-files | grep "\.h" | xargs wc -l').read() # findstr "total"
out_cpp += os.popen('cd "PSiO Team Project" && git ls-files | grep "\.cpp" | xargs wc -l').read() # findstr "total"

total_h = int(out_h.split('\n')[-2].split()[0]) # last line has a total number as a first word
total_cpp = int(out_cpp.split('\n')[-2].split()[0]) # last line has a total number as a first word
total = total_h + total_cpp
total_text = f'--- TOTAL: {total} ---'

print(out_h, out_cpp, total_text, sep='\n')
