set ns [new Simulator]

$ns rtproto DV

$ns color 0 "blue"
$ns color 1 "pink"

set f [open out.tr w]
$ns trace-all $f

set nf [open out.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n3 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms RED
$ns duplex-link $n1 $n2 1Mb 10ms RED
$ns duplex-link $n2 $n3 1Mb 10ms RED
$ns duplex-link $n3 $n0 1Mb 10ms RED

set tcp01 [new Agent/TCP]
$tcp01 set fid_ 0
set tcpsink01 [new Agent/TCPSink]
$ns attach-agent $n0 $tcp01
$ns attach-agent $n1 $tcpsink01
$ns connect $tcp01 $tcpsink01

set ftp01 [new Application/FTP]
$ftp01 attach-agent $tcp01

set tcp23 [new Agent/TCP]
$tcp23 set fid_ 1
set tcpsink23 [new Agent/TCPSink]
$ns attach-agent $n2 $tcp23
$ns attach-agent $n3 $tcpsink23
$ns connect $tcp23 $tcpsink23

set ftp23 [new Application/FTP]
$ftp23 attach-agent $tcp23

proc finish {} {
    global ns nf f
    $ns flush-trace
    close $nf
    close $f
    exec nam out.nam &
    exit 0
}

$ns at 0.5 "$ftp01 start"
$ns at 0.5 "$ftp23 start"
$ns rtmodel-at 2.0 down $n0 $n1
$ns rtmodel-at 3.0 up $n0 $n1
$ns at 4.5 "$ftp01 stop"
$ns at 4.5 "$ftp23 stop"
$ns at 5.0 "finish"
$ns run
