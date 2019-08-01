Nikolaos Lionakis
AM 2900
HY-345 - Askisi 2


Sti sinartisi main() arxika elengxetai oti ta orismata
pou dinontai kata tin ektelesi tou programmatos einai swsta
kai an oxi, to programma termatizetai me ena mhnuma lathous.
Se epituxh ektelesi, arxika dimiourgountai sieriaka 2 threads pou
antistoixoun stous grocers kai me ti xrisi enos for() loop
dimiourgountai ta threads pou antistoixoun stous customers.
Xrisimopoiithikan 2 semaphores gia ton sugxronismo twn 
grocers kai customers kathws kai ena trito (san mutex) gia
to xeirismo twn chairs (to pote enas customer katalamvanei ena chair
kai pote to apeleutherwnei). Otan enas customer katafthasei alla
den uparxoun diathesima chairs, tote feugei kai auksanetai o 
sxetikos counter. O xronos anamonis gia kathe customer 
upologizetai apo ti stigmh pou tha prospathisei na ksupnhsei
enan grocer kai perimenontas tin apanthsh tou peutei o idios
gia upno. O sunolikos xronos anamonis apothikeuetai se ena
global sum kai o mesos oros upologizetai meta ton termatismo olwn twn
threads sthn main().