BEGIN {
sent=0
recv=0
}

{
  if($1=="s" && $4=="AGT") {
    sent++;
   }
  else if($1=="r" && $4=="AGT") {
     recv++;
   }
 
}
END {
 printf("Packets received:%d\n", recv)
 printf("Packets sent: %d\n", sent)
 printf("Packet Drop ratio:%.2f\n", (sent - recv)/recv)
}
