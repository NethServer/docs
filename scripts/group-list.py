#!/usr/bin/python

import xml.etree.ElementTree as ET
import sys

def help():
    print "Usage: group-list.py <group_xml_file> <lang>"
    sys.exit(1)

if (len(sys.argv) < 2):
    help()

gfile = sys.argv[1]
outlang = sys.argv[2]


groups = []

tree = ET.parse(gfile)
root = tree.getroot()
for g in root.iter('group'):
    id = g.find('id').text
    name = {}
    desc = {}
    for n in g.iter('name'):
        lang = "en"
        if "{http://www.w3.org/XML/1998/namespace}lang" in n.attrib:
            lang =  n.attrib["{http://www.w3.org/XML/1998/namespace}lang"]
        name[lang] = n.text
    for n in g.iter('description'):
        lang = "en"
        if "{http://www.w3.org/XML/1998/namespace}lang" in n.attrib:
            lang =  n.attrib["{http://www.w3.org/XML/1998/namespace}lang"]
        desc[lang] = n.text
        
        
    groups.append( {'id' : id , 'name' : name, 'desc' : desc} )    


excludes = ("buildsys-build", "centos-minimal", "nethserver-iso")

for g in groups:
   if g["id"] in excludes:
       continue

   if outlang in g["name"]:
       name = g["name"][outlang]
       desc = g["desc"][outlang]
   else:
       name = g["name"]["en"]
       desc = g["desc"]["en"]
   #print "* " + g["id"] + " - " + name + ": " + desc
   print "* **"+name+"** : " + desc + "\n   ID: ``"+g["id"] + "``"
