inline int next_int() {
    int n = 0;
    char c = getchar_unlocked();
	bool neg = false;
    while (!(c >= '0' && c <= '9')){
		if(c == '-'){
			c = getchar_unlocked();
			if(c >= '0' && c <= '9'){
				neg = true;
			}
		}else c = getchar_unlocked();
    }
    
    while ('0' <= c && c <= '9') {
		n = n * 10 + c - '0';
		c = getchar_unlocked();
    }
    
	if(neg) return -n;
	else return n;
}

inline char next_char(){
	char c = getchar_unlocked();
	while(c == ' ' || c == '\n') c = getchar_unlocked();
	return c;
}

inline string next_string(){
	string out;
	char c = getchar_unlocked();
	while(c == ' ' || c == '\n') c = getchar_unlocked();
	while(!(c == ' ' || c == '\n')){
		out.pb(c);
		c = getchar_unlocked();
	}
	
	return out;
}


bool read( int &n ) { 
    n = 0; 
    register bool neg = false; 
    register char c = getchar_unlocked(); 
    if( c == EOF) { n = -1; return false; } 
    while (!('0' <= c && c <= '9')) { 
        if( c == '-' ) neg = true; 
        c = getchar_unlocked(); 
    } 
    while ('0' <= c && c <= '9') { 
        n = n * 10 + c - '0'; 
        c = getchar_unlocked(); 
    } 
    n = (neg ? (-n) : (n)); 
    return true; 
} 
 
inline void writeInt(int n){ 
    register int idx = 20; 
    if( n < 0 ) putchar_unlocked('-'); 
    n = abs(n); 
    char out[21]; 
    out[20] = ' '; 
    do{ 
        idx--; 
        out[idx] = n % 10 + '0'; 
        n/= 10; 
    }while(n); 
    do{ putchar_unlocked(out[idx++]); } while (out[idx] != ' '); 
} 
 