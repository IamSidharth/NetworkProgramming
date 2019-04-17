# simple-wireless.tcl
# A simple example for wireless simulation

# ======================================================================
# Define options
# ======================================================================
set val(chan)           Channel/WirelessChannel    ;# channel type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         5                        ;# max packet in ifq
set val(nn)             3                         ;# number of mobilenodes
set val(rp)             DSDV                       ;# routing protocol
set val(x)              500;
set val(y)              400;
# ======================================================================
# Main Program
# ======================================================================


#
# Initialize Global Variables
#
set ns_		[new Simulator]
set tracefd     [open simple.tr w]
$ns_ trace-all $tracefd
set namtrace [open bhapith.nam w]
$ns_ namtrace-all-wireless $namtrace $val(x) $val(y)

# set up topography object
set topo       [new Topography]

$topo load_flatgrid 500 500

#
# Create god object
#
create-god $val(nn)

#
#  Create the specified number of mobilenodes [$val(nn)] and "attach" them
#  to the channel. 
#  Here two nodes are created : node(0) and node(1)

# configure node

$ns_ node-config -adhocRouting $val(rp) \
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
		 -movementTrace OFF			
			 
for {set i 0} {$i < $val(nn) } {incr i} {
	set node_($i) [$ns_ node]	
	$node_($i) random-motion 0		;# disable random motion
}

#
# Provide initial (X,Y, for now Z=0) co-ordinates for mobilenodes
#
$node_(0) set X_ 5.0
$node_(0) set Y_ 2.0
$node_(0) set Z_ 0.0

$node_(1) set X_ 60.0
$node_(1) set Y_ 60.0
$node_(1) set Z_ 0.0

$node_(2) set X_ 390.0
$node_(2) set Y_ 385.0
$node_(2) set Z_ 0.0

#
# Now produce some simple node movements
# Node_(1) starts to move towards node_(0)
#
$ns_ at 5.0 "$node_(2) setdest 70.0 70.0 10.0"
$ns_ at 5.0 "$node_(0) setdest 67.0 67.0 10.0"
$ns_ at 0.0 "$node_(1) setdest 60.0 60.0 0.0"
$ns_ at 200.0 "$node_(2) setdest 250.0 250.0 10.0"
$ns_ at 200.0 "$node_(0) setdest 10.0 10.0 10.0"


# Setup traffic flow between nodes
# TCP connections between node_(0) and node_(1)

set tcp [new Agent/TCP]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns_ attach-agent $node_(0) $tcp
$ns_ attach-agent $node_(1) $sink
$ns_ connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns_ at 0.0 "$ftp start" 

set tcp1 [new Agent/TCP]
$tcp1 set class_ 2
set sink1 [new Agent/TCPSink]
$ns_ attach-agent $node_(2) $tcp1
$ns_ attach-agent $node_(1) $sink1
$ns_ connect $tcp1 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ns_ at 0.0 "$ftp1 start" 
#
# Tell nodes when the simulation ends
#
#for {set i 0} {$i < $val(nn) } {incr i} {
   # $ns_ at 150.0 "$node_($i) reset";
#}
$ns_ at 260.0 "stop"
$ns_ at 260.01 "puts \"NS EXITING...\" ; $ns_ halt"
proc stop {} {
    global ns_ tracefd namtrace
    $ns_ flush-trace
    close $tracefd
   #close $namtrace
   exec nam bhapith.nam
}

puts "Starting Simulation..."
$ns_ run

