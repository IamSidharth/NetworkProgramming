set ns [new Simulator]

set f [open out.tr w]
$ns trace-all $f

set nf [open out.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n4 $n0 1Mb 10ms RED
$ns duplex-link $n4 $n1 1Mb 10ms RED
$ns duplex-link $n4 $n2 1Mb 10ms RED
$ns duplex-link $n4 $n3 1Mb 10ms RED

set udp03 [new Agent/UDP]
set udpsink03 [new Agent/Null]
$ns attach-agent $n0 $udp03
$ns attach-agent $n3 $udpsink03
$ns connect $udp03 $udpsink03

set cbr03 [new Application/Traffic/CBR]
$cbr03 attach-agent $udp03
$cbr03 set type_ CBR
$cbr03 set packet_size_ 1000
$cbr03 set rate_ 1Mb
$cbr03 set random_ false 

set udp12 [new Agent/UDP]
set udpsink12 [new Agent/Null]
$ns attach-agent $n1 $udp12
$ns attach-agent $n2 $udpsink12
$ns connect $udp12 $udpsink12

set cbr12 [new Application/Traffic/CBR]
$cbr12 attach-agent $udp12
$cbr12 set type_ CBR
$cbr12 set packet_size_ 1000
$cbr12 set rate_ 1Mb
$cbr12 set random_ false 

proc finish {} {
    global ns nf f
    $ns flush-trace
    close $nf
    close $f
    exec nam out.nam &
    exit 0
}

$ns at 0.5 "$cbr03 start"
$ns at 0.5 "$cbr12 start"
$ns at 10.5 "$cbr03 stop"
$ns at 10.5 "$cbr12 stop"
$ns at 11 "finish"
$ns run
