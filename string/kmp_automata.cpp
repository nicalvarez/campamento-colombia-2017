string s; // входная строка
const int alphabet = 256; // мощность алфавита символов, обычно меньше
 
s += '#';
int n = (int) s.length();
vector<int> pi = prefix_function (s);
vector < vector<int> > aut (n, vector<int> (alphabet));
for (int i=0; i<n; ++i)
	for (char c=0; c<alphabet; ++c)
		if (i > 0 && c != s[i])
			aut[i][c] = aut[pi[i-1]][c];
		else
			aut[i][c] = i + (c == s[i]);
