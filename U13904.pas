type type1=array [1..200000] of integer;
var ch:char;
    boo:boolean;
    pos,len,n1,nn1,n2,nn2:longint;
    num:type1;
function arr2ch(poss:longint):char;
var i,v233,tmp:longint;
begin
  v233:=1;
  tmp:=0;
  for i:=poss+4 downto poss do
  begin
    tmp:=num[i]*v233+tmp;
    v233:=v233*2;
  end;
  if tmp<=26 then exit(chr(tmp+ord('A')))
  else exit('0');
end;
function arr2num(poss:longint):longint;
var i,tmp,v233:longint;
begin
  v233:=1;
  tmp:=0;
  for i:=poss+6 downto poss do
  begin
    tmp:=num[i]*v233+tmp;
    v233:=v233*2;
  end;
  exit(tmp);
end;
begin
  boo:=true;
  pos:=0;
  while true do
  begin
    inc(pos);
    read(ch);
    if ch='0' then num[pos]:=0 else if ch='1' then num[pos]:=1 else if (ord(ch)=13) or (ord(ch)=10) then begin dec(pos); break; end;
  end;
  len:=pos;
  pos:=1;
  while pos<=len do
  begin
    if (num[pos]=1)
    and (num[pos+1]=0)
    and (num[pos+2]=1)
    and (arr2ch(pos+3)<>'0') then
    begin
      write(arr2ch(pos+3));
      pos:=pos+8;
    end else if (num[pos]=1) and (num[pos+1]=1) and (num[pos+2]=1) then
    begin
      write(' ');
      pos:=pos+8;
    end else if num[pos]=0 then
    begin
      n1:=arr2num(pos+1);
      if num[pos+8]<>0 then boo:=false;
      n2:=arr2num(pos+9);
      nn1:=n1 div 2;
      nn2:=n2 div 2;
      write(nn1+nn2);
      pos:=pos+16;
    end else boo:=false;
  end;
  if not boo then write('Error');
end.
