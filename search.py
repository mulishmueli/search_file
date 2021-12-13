import os
import time
import stat
import csv
import datetime as dt
import sys

root = 'C:\Windows'
b= []
for path, subdirs, files in os.walk(root):
    for f in files:
        full_path = os.path.join(path, f)
        os.path.isfile(full_path)
        try:
            modification_time = os.path.getatime(full_path)
            act = time.ctime(modification_time)
        except OSError:
            act = 0

        try:
            modt = time.ctime(os.path.getmtime(full_path))
        except OSError:
            modt = 0

        try:
            cret = time.ctime(os.path.getctime(full_path))
        except OSError:
            cret = 0

        fp = full_path
        fi = f
        print(fp)
        print(f)
        now = dt.datetime.now()
        ago = now-dt.timedelta(minutes=60)
        try:
            st = os.stat(fp) 
            mtime = dt.datetime.fromtimestamp(st.st_mtime)
        except OSError:
            mtime = now-dt.timedelta(minutes=61)

        if  fp.find('C:\\Windows\\addins', 0 , 19) != -1 or mtime > ago or fi == 'ERRORRED' or fi.find('QHE', 0 , 3) != -1 or fi.find('GNOFF', len(fi)-5 , len(fi)) != -1 or fi.find('XT.ec') != -1 or fi.find('AcGenral') != -1 or fi.find('.sdb', len(fi)-4, len(fi)) != -1 :
            a = []
            a.append(full_path)
            a.append(f)
            a.append(act)
            a.append(modt)
            a.append(cret)
            b.append(a)

with open('result.csv', 'w', newline='') as file:
    fields = ['FolderPath','FileName','DateAccessed','ModifiedDate','CreationDate'] 
    writer = csv.writer(file)
    writer.writerow(fields) 
    writer.writerows(b)
