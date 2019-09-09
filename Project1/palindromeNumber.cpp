class Solution {
public:
    bool isPalindrome(int x) {
        vector<int> vet;
        int temp;
        if(x<0)
            return false;
        else if(x==0)
            return true;
        
        while(x)
        {
            temp = x%10;
            vet.push_back(temp);
            x = x/10;
        }
        temp = vet.size();
        for(auto i=0; i<= temp/2; ++i)
        {
            if(vet[i] != vet[temp-1-i])
                return false;
        }
        return true;
        
    }
};
//  花费时间44ms
