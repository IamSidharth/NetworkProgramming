BEGIN {
       recvdSize = 0
       startTime = 400
       stopTime = 0
	drop = 0
	sent = 0
	receive = 0
  }
   
  {
             event = $1
             time = $2
             node_id = $3
             pkt_size = $8
             level = $4
   
  # Store start time
  if ((level == "AGT" || level == "IFQ") && (event == "s") && pkt_size >= 512) {
    if (time < startTime) {
             startTime = time
             }
	sent+=1
       }
   
  # Update total received packets' size and store packets arrival time
  if ((level == "AGT" || level == "IFQ") && (event == "r") && pkt_size >= 512) {
       if (time > stopTime) {
             stopTime = time
             }
       # Rip off the header
       #hdr_size = pkt_size % 512
       #pkt_size -= hdr_size
       # Store received packet's size
       recvdSize += pkt_size
	receive +=1;
       }

if ((level == "AGT" || level == "IFQ") && (event == "d") && pkt_size >= 512) {
   
	drop+=1
       }


  }
   
  END {
       printf("Packet delivery ratio: %f",receive/(sent));
  }
