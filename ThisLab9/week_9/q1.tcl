# Define options
set val(chan) Channel/WirelessChannel ;# channel type
set val(prop) Propagation/TwoRayGround ;# radio-propagation model
set val(netif) Phy/WirelessPhy ;# network interface type
set val(mac) Mac/802_11 ;# MAC type
set val(ifq) Queue/DropTail/PriQueue ;# interface queue type
set val(ll) LL ;# link layer type
set val(ant) Antenna/OmniAntenna ;# antenna model
set val(ifqlen) 50 ;# max packet in ifq
set val(nn) 10 ;# number of mobile nodes
set val(rp) AODV ;# routing protocol
set val(x) 500 ;# X dimension of topography
set val(y) 500 ;# Y dimension of topography
set val(stop) 150 ;# time of simulation end

set ns [new Simulator]
#creating trace file and nam file
set tracefd [open out.tr w]
$ns trace-all $tracefd
set namtrace [open out.nam w]
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

# set up topography object
set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)
create-god $val(nn)

# configure the nodes
$ns node-config -adhocRouting $val(rp) \
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

for {set i 0} {$i < $val(nn) } { incr i } {
  set node_($i) [$ns node] 
  $node_($i) random-motion 0

}

$node_(0) set X_ 250.0
$node_(0) set Y_ 250.0
$node_(0) set Z_ 0.0

for {set i 1} {$i < $val(nn) } { incr i } {
  $node_($i) set X_ 400.0
  $node_($i) set Y_ [expr $i*40 + 80]
  $node_($i) set Z_ 0.0
}

for {set i 0} {$i < $val(nn) } { incr i } {
  $ns initial_node_pos $node_($i) 30
}

  

set tcp [new Agent/TCP]
set udp [new Agent/UDP]
$ns attach-agent $node_(0) $tcp
$ns attach-agent $node_(0) $udp

set sink_2 [new Agent/TCPSink]
set sink_1 [new Agent/Null]
$ns attach-agent $node_(2) $sink_2
$ns attach-agent $node_(1) $sink_1

$ns connect $tcp $sink_2
$ns connect $udp $sink_1

set ftp [new Application/FTP]
$ftp attach-agent $tcp

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp

$ns at 20.0 "$ftp start"
$ns at 20.0 "$cbr start"

# Telling nodes when the simulation ends
for {set i 0} {$i < $val(nn) } { incr i } {
  $ns at $val(stop) "$node_($i) reset";
}

# ending nam and the simulation
$ns at $val(stop) "stop"
$ns at [expr $val(stop) + 0.01 ] "puts \"end simulation\" ; $ns halt"

proc stop {} {
  global ns tracefd namtrace
  $ns flush-trace
  close $tracefd
  close $namtrace
  exec nam out.nam &
}

$ns run
