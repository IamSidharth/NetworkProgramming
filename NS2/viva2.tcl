set ns [new Simulator]


$ns color 0 "red"

set f [open out.tr w]
$ns trace-all $f

set nf [open out.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$n2 shape "square"


$ns duplex-link $n0 $n1 1Mb 10ms RED orient right
$ns duplex-link $n1 $n2 1Mb 10ms RED orient up
$ns duplex-link $n2 $n3 1Mb 10ms RED orient right




set udp02 [new Agent/UDP]
set udpsink00 [new Agent/Null]
$udpsink00 set fid_ 0
$ns attach-agent $n2 $udp02
$ns attach-agent $n0 $udpsink00
$ns connect $udp02 $udpsink00

set cbr02 [new Application/Traffic/CBR]
$cbr02 attach-agent $udp02
$cbr02 set type_ CBR
$cbr02 set packet_size_ 1000
$cbr02 set rate_ 1Mb
$cbr02 set random_ false 

 

proc finish {} {
    global ns nf f
    $ns flush-trace
    close $nf
    close $f
    exec nam out.nam &
    exit 0
}

$ns at 0.5 "$cbr02 start"
$ns at 10.5 "$cbr02 stop"
$ns at 11 "finish"
$ns run