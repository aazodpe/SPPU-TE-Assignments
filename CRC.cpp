#include<bits/stdc++.h>
using namespace std;

class crc{
    public:
    static string dec_binary(int dec){
    if(dec<1)
        return "0";

    string binstr =" ";
    while(dec>0){
        binstr = binstr.insert(0, string(1, (char)((dec%2)+48)));
        dec /= 2;
        }
        return binstr;
    }

    static string ascii_binary(string str){
        string bin="";
        int strlength = str.length();
        for(int i = 0; i<strlength; i++){
            string cbin = dec_binary(str[i]);
            int cbinlength = cbin.length();
            if(cbinlength<8){
                for(size_t i = 0; i<(8-cbinlength); i++)
                cbin = cbin.insert(0, "0");
            }
            bin+=cbin;
        }
        return bin;
    }


    string xor1(string a, string b){
        string result = "";
        int n = b.length();

        for(int i = 1; i<n; i++){
            if(a[i] == b[i])
                result += "0";
            else
                result += "1";
        }
        return result;
    }

    string mod2div(string dividend, string divisor){
        int pick = divisor.length();
        string tmp = dividend.substr(0,pick);
        int n = dividend.length();
        while(pick<n){
            if(tmp[0] == '1')
                tmp = xor1(divisor, tmp) + dividend[pick];
            else
                tmp = xor1(std::string(pick,'0'),tmp) + dividend[pick];
        pick+=1;
        }
        if(tmp[0] == '1')
            tmp = xor1(divisor,tmp);
        else
            tmp = xor1(std::string(pick, '0'), tmp);
        return tmp;
    }

    void encode_data(string data, string key){
        int lkey = key.length();
        string appended = (data+std::string(lkey - 1, '0'));
        string remainder = mod2div(appended, key);
        string coded = data + remainder;
        cout<<"Remainder: "<<remainder<<"\n";
        cout<<"Encoded Data (Data + Remainder): "<<coded<<"\n";
    }


    void receiver(string data, string key){
        string curr_xor = mod2div(data.substr(0, key.size()), key);
        int curr = key.size();
        while(curr != data.size()){
            if(curr_xor.size() != key.size())
                curr_xor.push_back(data[curr++]);
            else
                curr_xor = mod2div(curr_xor, key);
        }
        if(curr_xor.size() == key.size())
            curr_xor = mod2div(curr_xor, key);
        if(curr_xor.find('1') != string :: npos)
            cout<<"There is error in data"<<endl;
        else
            cout<<"No error in data"<<endl;
    }
};


int main(){
    crc c;
    string d;
    string key;
    cout<<"Enter string/message: ";
    cin>>d;
    cout<<"Enter key/divisor: ";
    cin>>key;
    
    string conv = c.ascii_binary(d);    //convert string to binary
    cout<<"Sender Side: "<<endl;
    c.encode_data(conv, key);

    cout<<"\nReceiver Side: "<<endl;
    c.receiver(conv+c.mod2div(conv+std::string(key.size()-1, '0'),key), key);

}
