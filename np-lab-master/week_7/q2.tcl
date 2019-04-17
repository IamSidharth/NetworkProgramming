set ns [new Simulator]

$ns color 1 blue
$ns color 2 red

set nf [open out.nam w]
$ns namtrace-all $nf

set f [open out.tr w]
$ns trace-all $f

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms RED
$ns duplex-link $n1 $n2 1Mb 10ms RED
$ns duplex-link $n2 $n3 1Mb 10ms RED
$ns duplex-link $n3 $n0 1Mb 10ms RED

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient down
$ns duplex-link-op $n2 $n3 orient left
$ns duplex-link-op $n3 $n0 orient up

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
$tcp0 set class_ 1

set tcp1 [new Agent/TCP]
$ns attach-agent $n2 $tcp1
$tcp1 set class_ 2

set sink0 [new Agent/TCPSink]
$ns attach-agent $n1 $sink0

set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1

$ns connect $tcp0 $sink0
$ns connect $tcp1 $sink1

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1


proc finish {} {
  global ns nf f
  $ns flush-trace
  close $nf
  close $f
  exec nam out.nam &
  exit 0
}

$ns at 0.1 "$ftp0 start"
$ns at 0.2 "$ftp1 start"

$ns at 0.9 "$ftp0 stop"
$ns at 0.9 "$ftp1 stop"

$ns at 10.0 "finish"

$ns run
