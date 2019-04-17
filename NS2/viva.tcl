set ns [new Simulator]

$ns rtproto DV

$ns color 0 "red"
$ns color 1 "pink"

set f [open out.tr w]
$ns trace-all $f

set nf [open out.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link-op $n0 $n1 1Mb 10ms RED 
$ns duplex-link-op $n1 $n2 1Mb 10ms RED 
$ns duplex-link-op $n2 $n3 1Mb 10ms RED 



#$n1 set fid_ 0
$n1 color "red"


set tcp01 [new Agent/TCP]
set tcpsink01 [new Agent/TCPSink]
$ns attach-agent $n0 $tcp01
$ns attach-agent $n3 $tcpsink01
$ns connect $tcp01 $tcpsink01

set ftp01 [new Application/FTP]
$ftp01 attach-agent $tcp01


proc finish {} {
    global ns nf f
    $ns flush-trace
    close $nf
    close $f
    exec nam out.nam &
    exit 0
}

$ns at 0.5 "$ftp01 start"
$ns rtmodel-at 2.0 down $n1 $n2
$ns rtmodel-at 2.5 up $n1 $n2
$ns at 4.5 "$ftp01 stop"
$ns at 5.0 "finish"
$ns run