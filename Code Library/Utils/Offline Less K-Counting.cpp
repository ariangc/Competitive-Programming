//-------------------inversiones en un rango (offline)----------------
// ar[]: arreglo, queries=queri.pb(l,r,valor)
//assignar n,q; ez[i] respuesta para la querie i
//hacer read y make; 

struct ST{
  ll n,q;
  vector<tri> querie;
  ll t[2*N],ar[N];
  ll poar[N],pok[N],ark[N],ez[N];
  vii v,v1;
  inline ll Op(ll &a,ll &b){ return a+b;}
  inline void build (){
    RREP(i,n-1,1) t[i]=Op(t[i<<1],t[i<<1|1]);
  }
  inline void modify (ll p, ll val){
    for(t[p+=n]=val;p>1;p>>=1) t[p>>1]=Op(t[p],t[p^1]);
  }
  inline ll que(ll l, ll r){
    ll res=0; 
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
      if(l&1) res+=t[l++];
      if(r&1) res+=t[--r];
    }
    return res;
  }
  ll p1=0, p2=0,po=0;
  inline void read(){
    REP(i,0,n) v.push_back({ar[i],i});
    sort(all(v));
    REP(i,0,n) poar[p1++]=v[i].snd;
    REP(u,0,q){
      ll k=querie[u].itm3;
      ark[u]=k; 
      v1.push_back({k,u});
    }
    sort(all(v1));
    REP(i,0,q) pok[p2++]=v1[i].snd;
  }
  inline void make(){
    REP(i,0,n) t[i+n]=0; build();
    REP(i,0,q){
      ll x=pok[i];
      // <k, <= k en l,r(despues del &&)
      //inversa , hacer t[i+n]=1; 
      while(po<n && ar[poar[po]]<=ark[x]) modify(poar[po++],1);
      ez[x]=que(querie[x].itm1-1,querie[x].itm2);
    }
  }
}st;

int main(){fastio;
  ll n; cin>>n;
  st.n=n;
  REP(i,0,n) cin>>st.ar[i]; 
  ll q; cin>>q;
  st.q=q;
  REP(i,0,q){
    ll l,r,k; cin>>l>>r>>k;
    st.querie.push_back({l,{r,k}});
  }
  st.read(); st.make();
  REP(i,0,q) cout<<st.ez[i]<<endl;
  return 0;
}