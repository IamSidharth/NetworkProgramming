
set val(chan) Channel/WirelessChannel
set val(prop) Propagation/TwoRayGround
set val(netif) Phy/WirelessPhy
set val(mac) Mac/802_11
set val(ifq) Queue/DropTail/PriQueue
set val(ifqlen) 50
set val(ll) LL
set val(ant) Antenna/OmniAntenna
set val(nn) 10
set val(rp) DSDV
set val(x) 500
set val(y) 500
set val(stop) 150

set ns [new Simulator]
set tracefd [open out1.tr w]
set namtrace [open out1.nam w]

$ns trace-all $tracefd
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)

create-god $val(nn)

$ns node-config \
  -adhocRouting $val(rp) \
  -llType $val(ll) \
  -macType $val(mac) \
  -ifqType $val(ifq) \
  -ifqLen $val(ifqlen) \
  -antType $val(ant) \
  -propType $val(prop) \
  -phyType $val(netif) \
  -channelType $val(chan) \
  -topoInstance $topo \
  -agentTrace ON \
  -routerTrace ON \
  -macTrace OFF \
  -movementTrace ON

for { set i 0 } { $i < $val(nn) } { incr i } {
  set node_($i) [$ns node]
}

$node_(0) color red
$node_(1) color black
$node_(2) color green
$node_(3) color yellow
$node_(4) color blue
$node_(5) color red

$node_(0) set X_ 0.0
$node_(0) set Y_ 0.0
$node_(0) set Z_ 0.0

$node_(1) set X_ 40.0
$node_(1) set Y_ 100.0
$node_(1) set Z_ 0.0

$node_(2) set X_ 200.0
$node_(2) set Y_ 100.0
$node_(2) set Z_ 0.0

$node_(3) set X_ 40.0
$node_(3) set Y_ 10.0
$node_(3) set Z_ 0.0

$node_(4) set X_ 200.0
$node_(4) set Y_ 10.0
$node_(4) set Z_ 0.0


$node_(5) set X_ 300.0
$node_(5) set Y_ 50.0
$node_(5) set Z_ 0.0

$node_(6) set X_ 30.0
$node_(6) set Y_ 50.0
$node_(6) set Z_ 0.0

$node_(7) set X_ 70.0
$node_(7) set Y_ 40.0
$node_(7) set Z_ 0.0

$node_(8) set X_ 10.0
$node_(8) set Y_ 450.0
$node_(8) set Z_ 0.0

$node_(9) set X_ 450.0
$node_(9) set Y_ 10.0
$node_(9) set Z_ 0.0





$ns at 10.0 "$node_(0) setdest 20.0 50.0 2.5"


set tcp [new Agent/TCP/Newreno]
set sink [new Agent/TCPSink]
$ns attach-agent $node_(0) $tcp
$ns attach-agent $node_(1) $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns at 10.0 "$ftp start"

$ns at 50.0 "$ftp stop"


set tcp1 [new Agent/TCP/Newreno]
set sink1 [new Agent/TCPSink]
$ns attach-agent $node_(1) $tcp1
$ns attach-agent $node_(2) $sink1
$ns connect $tcp1 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ns at 10.0 "$ftp1 start"
$ns at 20.0 "$ftp1 stop"

set tcp2 [new Agent/TCP/Newreno]
set sink2 [new Agent/TCPSink]
$ns attach-agent $node_(2) $tcp2
$ns attach-agent $node_(5) $sink2
$ns connect $tcp2 $sink2
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ns at 11.0 "$ftp2 start"
$ns at 21.0 "$ftp2 stop"


for { set i 0 } { $i < $val(nn) } { incr i } {
  $ns initial_node_pos $node_($i) 15
  $ns at $val(stop) "$node_($i) reset";
}

$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 150.01 "$ns halt"

proc stop {} {
  global ns tracefd namtrace
  $ns flush-trace
  close $tracefd
  close $namtrace
  exec nam out1.nam & 
}

$ns run
