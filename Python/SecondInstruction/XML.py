from xml.dom.minidom import parse
import xml.dom.minidom

def replaceText(node, newText):
    if node.firstChild.nodeType != node.TEXT_NODE:
        raise Exception("Node does not contain text")
    node.firstChild.replaceWholeText(newText)

movies = xml.dom.minidom.parse('movies.xml') #ładowanie xmla
#print(movies.toxml()) #wyswietlanie zawartosi xmla w jego postaci

my_filmweb = movies.getElementsByTagName("movie")
for movie in my_filmweb:
    print('*****Movie*****')
    title = movie.getElementsByTagName('title')[0]
    #print('Title: {}'.format(title)) wyswietli cos takiego: Title: [<DOM Element: title at 0x7fe1ea031048>]
    #Musisz się dostać do rzeczywistego napisu, który chowa się w węźle potomnym i wspomóc się atrybutem data
    print('Title: {}'.format(title.childNodes[0].data))
    type = movie.getElementsByTagName('type')[0]
    print('Type: {}'.format(type.childNodes[0].data))
    country = movie.getElementsByTagName('country')[0]
    print('Country: {}'.format(country.childNodes[0].data))
    year = movie.getElementsByTagName('year')[0]
    print('Year: {}'.format(year.childNodes[0].data))

    replaceText(type, "dziala")

file_handle = open('movies.xml','w')
movies.writexml(file_handle)
file_handle.close()
