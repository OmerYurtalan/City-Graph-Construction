#include<iostream>
#include <vector>

#include<fstream>
#include<string>

#include <algorithm>

#include <set>
using namespace std;
string str;
string str2;
class Graph {

public:

    Graph(int V) {
        this->V = V;        //constructor

    }
    /*void neighbors(int x) {


    }*/
    void add_vertex(string x) {
        labesOfNodes.push_back(x);      //þehir ekleme
    }
    void addEdge(int s, int d, int val) {
        adj[s].push_back(make_pair(d, val));        // þehirler arasý baðlantý kurma mesafeler dahil

        /* adj[d].push_back(s);*/
    }
    int get_vertex_value() {
        return V;               // deðer isteme
    }
    void set_vertex_value(int V) {
        this->V = V;            //deðer atama
    }
    vector<string> getlabelCity() {
        return labesOfNodes;        // sehirleri isteme
    }
    void sort() {
        for (int i = 0; i < V; i++) {

            std::sort(adj[i].begin(), adj[i].end(), [](const auto& left, const auto& right) { // mesafelerin olduðu second deðerleri alýp sort algortimasý kullanýyor
                return left.second < right.second;                                            //
                });
        }
    }
    void print() {
        /*for (int d = 0; d < V; ++d) {
            cout << "\n Vertex "
                << d << ":";
            for (auto x : adj[d])
                cout << "-> " << x;
            printf("\n");
        }*/
        for (int u = 0; u < V; u++)
        {
            int v, w;
            cout << " " << labesOfNodes[u] << " makes an edge with \n";
            for (auto it = adj[u].begin(); it != adj[u].end(); it++)
            {
                v = it->first;                                      //  sehir adý
                w = it->second;                                     //  mesafesi
                cout << "\t " << labesOfNodes[v] << " with edge weight ="//    sehirin plakasýndan ismin bulma ve yazdýrma
                    << w << "\n";
            }
            cout << "\n";
        }

    }
    void print2(int yay, int see) {

        int v, w;


        cout << " " << labesOfNodes[yay] << " makes an edge with \n";

        int i = 0;
        for (auto it = adj[yay].begin(); it != adj[yay].end(); it++)
        {

            v = it->first;
            w = it->second;

            cout << "\t " << labesOfNodes[v] << " with edge weight ="//
                << w << "\n";                                //
            i++;
            if (i == see) {                                 // ilk print iþlemindeki gibi yazdýrma iþlemi fakat see eþit olana kadar 
                break;                                      //
            }
        }



    }
    /* bool adjacent(int a, int b) {
         for (auto x : adj[a])
             if (x == b) {
                 return true;
             }
         return false;
     }*/
    int dijkstra(string str, string str2) {
        int keep1;
        int keep2;
        int num = 0;
        for (int i = 0; i < V; i++) {
            if (str == labesOfNodes[i]) {
                keep1 = i;                    //þehir plakasý
                num++;
            }
            if (str2 == labesOfNodes[i]) {
                keep2 = i;
                num++;
            }
        }
        if (num != 2) {             //þehirler eþleþmiyosa kurtulma için kontrol
            return 0;
        }


        set<pair<int, int>> pq_set; // Küçükten büyüðe doðru mesafelerle eþleþen þehirlerin kümesi
        vector<int> distance(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);

        pq_set.insert({ 0, keep1 });
        distance[keep1] = 0;

        while (!pq_set.empty()) {
            int u = pq_set.begin()->second;
            pq_set.erase(pq_set.begin());

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (distance[u] + weight < distance[v]) {
                    pq_set.erase({ distance[v], v });
                    distance[v] = distance[u] + weight;
                    parent[v] = u; // Parent bilgisini güncelledik
                    pq_set.insert({ distance[v], v });
                }
            }
        }
        printDijkstraResult(keep1, keep2, parent, distance);
    }



private:
    int V; // number of vertices
    //int E; // number of edges
    vector<string> labesOfNodes;         //þehirleri string þeklinde tut
    vector<pair<int, int> > adj[81];    //komþularý ve aralarýndaki mesafeyi tutuyor


   
    void printDijkstraResult(int source, int destination, const vector<int>& parent, const vector<int>& distance) {
        cout << "Shortest path from " << labesOfNodes[source] << " to " << labesOfNodes[destination] << ":\n";
        printPath(destination, parent);
        cout << "\nTotal distance: " << distance[destination] << endl;
    }

    void printPath(int current, const vector<int>& parent) {
        if (current == -1) return;
        printPath(parent[current], parent);
        cout << labesOfNodes[current];
        if (current != parent.size() - 1) 
            cout << " -> ";
    }

   

};
string fixedName(string str) {
    if (!str.empty()) {
        str[0] = toupper(str[0]);   //ilk harf büyüt

        // Diðer harfleri küçük yap
        for (size_t i = 1; i < str.length(); ++i) {
            str[i] = tolower(str[i]);       // diðerlerini küçült
        }
    }
    return str;
}
void enterCity() {
    cout << "enter city" << endl;
    cin >> str;
    str = fixedName(str);         //sehrin isminin ilk harfini büyük diðerlerini küçük yazmamýza olanak saðlýyor çünkü txt dosyamýzdakiler böyle

}

void printCity() {
    cout << str << endl;
}
int takeDistance(int o, int j, vector<string> userString2[]) {

    int sayiInt = stoi(userString2[o + 1][j + 2]); // string to int
    return sayiInt;
}

string takeLine[81];

vector<string> v;
int main() {
    int i = 0;
    int a = 0;

    Graph graph(0);



    vector<string> userString[81];
    ifstream file("adjacent cities.txt"); // veri çekmek

    while (getline(file, takeLine[i], '\n')) {
        //
        i++;                                        //satýr satýr bilgileri alma ve kaç satýr olduðunu sayma
    }                                               //
    size_t virgulIndeksi = 0;
    int r = 0;
    while (a < i) {

        while ((virgulIndeksi = takeLine[a].find(',')) != string::npos) {  //',' ün kaçýncý sýrada olduðunu bulma

            userString[a].push_back(takeLine[a].substr(0, virgulIndeksi));  //','e kadar olan kýsmý userString'e pushlama

            takeLine[a] = takeLine[a].substr(virgulIndeksi + 1);    //eklenen þehri çýkarma

        }

        userString[a].push_back(takeLine[a].substr(0, virgulIndeksi)); //
        //
        takeLine[a] = takeLine[a].substr(virgulIndeksi + 1);           //son kýsýmda , olmadýðý için sonuncuyu ayrýyeten alma iþlemi
        //
        virgulIndeksi = 0;                                             //

        r = graph.get_vertex_value();   // þehir sayýsý tutma
        graph.set_vertex_value(++r);    //


        a++;
    }
    for (int i = 0; i < 81; i++) {
        graph.add_vertex(userString[i][0]); //Graph clasýndaki labelOfNode içine þehirleri tek tek ekleme iþlemi
    }


    a = 0;
    i = 0;
    vector<string> userString2[82];
    string takeLine2[82];

    ifstream file2("CityDistancesFile.txt");

    while (getline(file2, takeLine2[i], '\n')) {    //
        // yukardaki iþleme benzer iþlem
        i++;                                        //
    }                                               //
    size_t virgulIndeksi2 = 0;
    while (a < i) {

        while ((virgulIndeksi2 = takeLine2[a].find(';')) != std::string::npos) {//
            //
            userString2[a].push_back(takeLine2[a].substr(0, virgulIndeksi2));   // benzer iþlem yine

            takeLine2[a] = takeLine2[a].substr(virgulIndeksi2 + 1);             //

        }

        userString2[a].push_back(takeLine2[a].substr(0, virgulIndeksi2));       //

        takeLine2[a] = takeLine2[a].substr(virgulIndeksi2 + 1);                 //ayný þekilde benzer iþlem

        virgulIndeksi2 = 0;                                                     //

        a++;
    }

    int o = 0;
    int k = 1;

    while (o < graph.get_vertex_value()) {
        int j = 0;
        while (j < graph.get_vertex_value()) {

            if (userString[o][k] == userString[j][0]) // þehirlerin numarasýný öðrenmek için kullanýlýyor
            {
                int val = takeDistance(o, j, userString2); // txt dosyasýndan mesafeyi alma iþlemi
                graph.addEdge(o, j, val);                   //baðlantýlý þehri belirleme (mesafeleri ile birlikte)



                if (userString[o].size() - 1 == k) {    //
                    k = 1;                              //

                    break;                              //  son elemana geldiðinde bu iþlemi bitirmek için 
                }                                       //
                k++;
                j = 0;
                continue;
            }
            j++;
        }
        o++;
    }
    graph.sort();                   // graphtaki þehirlerin mesafesini sýralamak için kullanýlýr
   // graph.print();                  // baþlangýçta sehirleri ve gidebileceði yerleri çýktý olarak gösteriyor

    /*bool check = graph.adjacent(66, 81);*/
    /*cout << check;*/
    int num = 0;

    vector <string> stl;
    int yay;
    int see;
    char menu;
    int keep = 0;
    do {
        cout << endl << "a. Enter city(or select)" << endl << "b. Print selected(or entered) city" << endl << "c. List k closest  cities (to selected city)" << endl << "d. Find shortest path to" << endl << "x. exit" << endl;
        cin >> menu;
        switch (menu) {
        case  'a':
            yay = -1;
            keep = 1;
            enterCity();            //sehir girmemizi istiyor
            stl = graph.getlabelCity();  //stle bulunan þehirlerin tamamýný ekle
            for (int i = 0; i < 82; i++) {
                if (stl[i] == str) {
                    yay = i;                //girilen þehrin plaka kodunu alma (yay deðiþkeni)
                    break;
                }
            }
            if (yay == -1) {
                cout << "you need to enter real city name" << endl;
            }
            break;
        case 'b':
            if (keep == 1) {
                printCity();            // þehir adýný düzeltilmiþ bir þekilde yazdýrma iþlemi
            }
            else {
                cout << "first enter city";
            }
            if (yay == -1) {
                cout << "you need to enter real city name" << endl;
            }
            break;
        case 'c':
            if (yay == -1) {
                cout << "first enter city" << endl;
                break;
            }
            if (keep == 1) {

                cout << "How many cities do you want to see the shortest route to? Please Enter ";
                cin >> see;             // kaç þehir görmek istiyorsun
                
                if (userString[yay].size()-1 < see) {          //
                    cout << "too many number" << endl;  //az önce aldýðýmýz yay deðiþkeni alýnabilecek þehir sayýsýný korumamýzý saðlýyor
                   
                    break;                              //
                }
                graph.print2(yay, see);                  //gidilebilcek yakýn þehirleri yazdýrma
                //for (int i = 0; i < 81; i++) {
                //    if (userString[i][0] == str) {
                //       /* for (int j = 1; j < userString[i].size(); j++) {
                //            graph.neighbors()
                //        }*/
                //    }
                //}

            }
            else if (keep == 0) {
                cout << "first you have to enter new city" << endl;
            }

            break;
        case 'd':
            if (keep == 1) {
                cout << "where you want to go" << endl;
                cin >> str2;
                str2 = fixedName(str2);                 //þehir ismi düzeltme
                num = graph.dijkstra(str, str2);        //str ile str2 arasýndaki en kýsa yolu bulma algoritmasý
                if (num == 0) {
                    cout << "wrong city name.Please enter again" << endl;
                }
            }
            else {
                cout << "first enter a city";
            }

            break;
        case 'x':
            cout << endl << "bye bye ";
            break;
        default:
            cout << "Wrong Input please enter agein" << endl;
            break;
        }



    } while (menu != 'x');


}