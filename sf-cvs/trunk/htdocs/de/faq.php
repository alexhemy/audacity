<?php BoxTop("Frequently Asked Questions"); ?>

<!--
<table width=100% cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+3">Frequently Asked Questions</font>
</td></tr></table>
-->

<p>

Allgemein:<br>
<a href="#g1">Ist Audacity wirklich frei und was ist der Grund daf�r?</a><br>
<a href="#g2">Wer entwickelt Audacity?</a><br>
<a href="#g3">Wie kann ich helfen?</a><br>
<a href="#g4">Ich habe einen Fehler gefunden! Was jetzt?</a><br>
<p>
Installation:<br>

<a href="#i1">Windows: Was soll ich mit der .exe Datei?</a><br>
<a href="#i2">Windows: Wie entferne ich Audacity?</a><br>
<a href="#i3">Mac: Was soll ich mit der .sit Datei machen?</a><br>
<a href="#i4">Unix: Warum habe ich fehlende Abh�ngigkeiten, wenn ich das .rpm Paket installieren will?</a><br>
<a href="#i5">Unix: Warum erhalte ich eine Fehlermeldung, wenn die Bibliothek libwx_gtk.so l�dt?</a><br>
<p>
Verwendung:<br>
<a href="#a1">Wie kann ich zwei St�cke mixen?</a><br>
<a href="#a2">Kann man Stimmen entfernen?</a><br>

<a href="#a3">Wenn ich versuche Harmonien aufzunehmen sind beide St�cke nicht zeitgleich bzw. nicht synchron ?
             </a><br>
<a href="#a4">Warum wird bei Audacity kein MP3 encoder mitgeliefert?</a><br>
<a href="#a5">Kann man RealAudio oder anderes "gestreamte audio" aufnehmen ?</a><br>
<a href="#a6">Hilfe! Ich dr�cke Aufnahme, aber alles was ich bekomme ist "Stille"!</a><br>
<a href="#a7">Wie trenne ich ein Lied (Track) in verschiedene St�cke ?</a><br>
<a href="#a8">Wie bekomme ich die Lieder von einer Audio CD ?</a><br>

<p>

<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">Allgemein</font>
</td></tr></table>

<p>

<a name="g1"></a>
<font size=+1><b>
1. Ist Audacity wirklich frei und was ist der Grund daf�r?<br>
</b></font>

<p>
Ja, es ist in jeder Hinsicht frei. Audacity steht nicht nur kostenlos zum Download zur Verf�gung,
Sie haben auch alle Freiheiten bei der Benutzung des Programms.

<p>
Audacity wird unter der
<a href="http://www.gnu.org/copyleft/gpl.html"
>General Public License (GPL)</a> vertrieben.
Sie k�nnen das Programm sowohl f�r private als auch f�r berufliche Zwecke verwenden.
Weitergabe und Verkauf sind erlaubt. Der Quelltext ist frei verf�gbar und darf beliebig
ver�ndert werden, sofern die �nderungen unter der GPL ver�ffentlicht werden.

<p>
Audacity wurde in Verwendung von wxWindows, eine Bibliothek die unter der weniger
restriktiven LGPL vertrieben wird, entwickelt.
F�r n�here Informationen besuchen Sie die Projektseite
<a href="http://www.wxwindows.org">wxwindows.org</a>.

<p>
Die Autoren von Audacity entschieden sich aus mehreren Gr�nden f�r die GPL.
Einige sind einfach freundliche Menschen, andere sind der Meinung,
dass Software grunds�tzlich frei sein sollte. Wieder andere glauben,
dass es gleicherma�en freie <b>und</b> kommerzielle Software geben sollte.
Ein wichtiger Grund ist wohl, dass das Programm so viel schneller bekannt wird.
Viele von uns sehen lieber Millionen zufriedene Menschen,
die Audacity zum Nulltarif einsetzen als vielleicht tausend zahlende Anwender.

<p>
Weiterhin sind f�r ein freies Projekt mehr Mitarbeiter zu finden.
W�re Audacity Shareware, w�re es fraglich ob dutzende Entwickler auf der ganzen Welt Code,
Fehlerbereinigungen, Dokus und Grafiken beisteuerten.
Wo w�re das Programm dann jetzt?

<p>
<a name="g2"></a>
<font size=+1><b>
2. Wer entwickelt Audacity?<br>
</b></font>

<p>
Dominic Mazzoni startet die Entwicklung von Audacity im Herbst 1999, w�hrend er Student an der Carnegie Mellon University in Pittsburgh, PA, USA war. Er arbeitet an einer Forschungsarbeit mit seinem Professor Roger Dannenberg und sie ben�tigten ein Programm, das Audioanalysen bildlich sichtbar machte. Nach einiger Zeit entwickelte das Programm sich zu einem, f�r viele Zwecke einsetzbare, Audiobearbeitungsprogramm und andere Leute beteiligten sich an der Weiterentwicklung.
<p>
Heute wird das Programm mit Hilfe von Sourceforge entwickelt,
wodurch viele Menschen �ber das Internet an freien Softwareprojekten zusammenarbeiten k�nnen.
F�r n�here Informationen gibt es die Seite
 <a href="http://www.sourceforge.net"
>sourceforge.net</a>.
Dutzende Entwickler haben zur Entwicklung von Audacity beigetragen und das Programm
wird kontinuierlich verbessert..

<p>
<a name="g3"></a>
<font size=+1><b>
3. Wie kann ich helfen?<br>
</b></font>

<p>
Suchen Sie Fehler und teilen Sie uns die Fehler mit.
Schreiben Sie Code. �bersetzen Sie das Prorgamm in Ihre Sprache. Entwerfen Sie Graphiken.
Tragen Sie sich in die Benutzer-Mailingliste von Audacity ein. Spenden Sie Geld.

<p>
Schauen Sie doch einmal bei unserer <?php print "<a href=donatetime.php?$langLinkStr>"; ?>Spenden-Seite</a>
 vorbei, um n�heres zu erfahren.
<p>

<a name="g4"></a>
<font size=+1><b>
4. Ich habe einen Fehler gefunden! Was nun?<br>
</b></font>

<p>
Posten Sie den Fehler bitte im <a href="http://audacity.fuchsi.de/">Audacity-Forum.</a>
Das wichtigste bei einem Fehlerreport ist die Pr�zision.
Wir brauchen so viele Information wie nur m�glich, um den Fehler reproduzieren zu k�nnen,
ansonsten k�nnen wir ihn schlecht ausbessern.

<p>
Lassen Sie uns wissen, welches Betriebssystem Sie verwenden
(z.B. Windows XP, MacOS X, Fedora Core, etc.) und
welche Hardware vielleicht etwas mit dem Fehler zu tun haben k�nnte.

<p>
Ist der Fehler reproduzierbar? Wenn er regelm��ig auftritt,
sagen Sie uns Schritt f�r Schritt, welche Operationen durchzuf�hren sind,
damit sich der Fehler bemerkbar macht. Wenn Sie eine Fehlermeldung erhalten,
vergessen Sie bitte nicht, uns den genauen Wortlaut der Meldung mitzuteilen.

<p>
Wir wollen alle Fehler bereinigen! Vielen Dank im Voraus f�r Ihre Mithilfe.

<p>
<br>
<p>

<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">Installation</font>
</td></tr></table>

<p>
<a name="i1"></a>
<font size=+1><b>
1. Windows: Was fange ich mit der .exe Datei an?<br>
</b></font>

<p>
W�hlen Sie im Browser die Option "Speichern" und speichern Sie die Datei in einem Ordner, den Sie
im Explorer wiederfinden. Starten Sie den Explorer, w�hlen Sie den Ordner aus und doppelklicken
Sie die Datei um das Setup zu starten. Dann werden die Programmdateien installiert und die
Startmen�eintrage erstellt.

<p>
Wenn Sie die .exe bereits heruntergeladen haben, doppelklicken Sie und das Setup wird gestartet.

<p>
Falls Sie nichts von Installationsroutinen halten, k�nnen Sie Sie auch das Zip Archiv herunterladen
und die Dateien (mit Winzip, PowerArchiver usw.) in ein beliebiges Verzeichnis entpacken.


<p>
<a name="i2"></a>
<font size=+1><b>
2. Windows: Wie entferne ich Audacity?<br>
</b></font>

<p>
Audacity kann in der Systemsteuerung unter "Software" deinstalliert werden:
W�hlen Sie den Eintrag "Audacity" und klicken Sie auf "Entfernen" - die Deinstallationsroutine
wird gestartet.

<p>
Im Fall der Zipdatei l�schen Sie das Programmverzeichnis

<p>
<a name="i3"></a> <font size=+1><b> 3. Mac: Was soll ich mit der .sit Datei?<br> </b></font>

<p>
Sie ben�tigen eine aktuelle Stufflt Expander Version.
Dieses Programm ist auf allen Macintosh-Computern vorhanden und
normalerweise in den Browser integriert. Falls das Archiv nicht automatisch
entpackt wird, ziehen Sie "audacity.sit" zum Stuffit Expander, um es zu entpacken.

<p>
Hier ist keine Installation mehr notwendig. Ziehen Sie lediglich den neuen
Ordner in Ihr Programme Verzeichnis.
Um Audacity zu entfernen, mu� nur das Verzeichnis gel�scht werden.

<p>
<a name="i4"></a>
<font size=+1><b>
4. Unix: Warum habe ich fehlende Abh�ngigkeiten, wenn ich das .rpm Paket installieren will?
<br></b></font>

<p>
Zun�chst stellen Sie bitte sicher, dass wxGTK installiert ist.
Dies kann zum Beispiel durch "rpm -qa | grep wxGTK" erfolgen - es sollte dann in etwa folgendes zu sehen
sein:<br>
<code>wxGTK-2.2.9-55<br>
wxGTK-devel-2.2.9-55</code><br>
Ein "rpm -q wxGTK" tut es zur Not auch ;)<br>
Die Links zu den erforderlichen Paketen sind auf auf unserer
<a href="http://audacity.sourceforge.net/unix.php">Linux-Seite</a> zu finden.
Falls beim Installationsversuch des Paketes eine Fehlermeldung erscheint obwohl die angemahnte
Bibliothek einwandfrei installiert ist, f�gen Sie einfach die Option "--nodeps" hinzu.

<p>
<a name="i5"></a>
<font size=+1><b>
5. Unix: Warum erhalte ich eine Fehlermeldung, wenn die Bibliothek library libwx_gtk.so geladen wird?<br></b></font>

<p>Das kann zwei Gr�nde haben:
<ul>
<li>Wenn Sie das wxWindows - RPM installiert haben, teilen Sie Ihrem System (als root)
das Vorhandensein der Bibliotheken mittels "ldconfig" mit.</li>
<li>Wenn Sie wxWindows selbst kompiliert haben, wird es warscheinlich in /usr/local sein.
/usr/local/lib ist aber oft nicht im Pfad (PATH) enthalten. Sie k�nnen den "Fehler" durch hinzuf�gen
des Pfades in der /etc/ld.so.conf beheben. Bei dieser Gelegenheit k�nnen Sie auch
gleich /usr/local/bin eintragen, damit das Programm "wx-config" gefunden wird.</li>
</ul>


<p>
<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">Arbeiten mit Audacity</font>
</td></tr></table>

<p>
<a name="a1"></a>
<font size=+1><b>
1. Wie kann ich zwei St�cke mixen?
</b></font>

<p>
Audacity mixt automatisch. Sie m�ssen lediglich zwei St�cke in das selbe Projekt importieren
(Import Audio). Wenn Sie den Aufnahme-Button bet�tigen, wird auch ein neuer Track erstellt.

<p>
Wenn Sie Ihr Projekt exportieren (wav, ogg, ...) werden alle Tracks zu einem St�ck "verschmolzen".
Den gleichen Effekt erzielt man durch "Quick Mix" im Project-Men�.

<p>
<a name="a2"></a>
<font size=+1><b>
2. Wie kann ich Stimmen aus St�cken entfernen?
</b></font>

<p>
Bei einigen Stereo-Aufnahmen ist es m�glich, die Stimmen zu entfernen weil die Stimme bei der
Studioaufnahme genau in der Mitte platziert wurde. Bei solchen St�cken kann man den rechten
Kanal vom Linken subtrahieren (oder umgekehrt) und die Stimmen sind entfernt.

<p>
<b>Das geht aber nur mit einigen wenigen Aufnahmen!</b>
<p>
Um das in Audacity zu bewerkstelligen, importieren Sie zun�chst einen Stereo - Track.
Klicken Sie das Trackmen� an (kleiner Pfeil, der nach unten zeigt) und w�hlen Sie "Split Stereo Track"
aus.
Nun haben Sie die beiden Kan�le getrennt und k�nnen einen davon ausw�hlen
indem Sie in den grauen Bereich links neben der Visualisierung des St�ckes klicken.
Im Effect-Men� finden Sie den Eintrag "Invert".  Durch Auswahl dieser Funktion wird der ausgew�hlte
Kanal invertiert. Dies f�hrt dazu, dass Signale, die zuvor sowohl im linken als auch im rechten Kanal
vorhanden waren, sich nun gegenseitig aufheben. In einigen F�llen kann mit dieser Methode der Gesang
ausgeblendet werden (Karaoke-Effekt). Das funktioniert aber nur bei manchen Aufnahmen.
Einfach probieren!

<p>
<a name="a3"></a>
<font size=+1><b>
3. When I try to record harmonies with myself,
              why are the two tracks out of sync?
</b></font>
<p>
Das ist normal und liegt daran, da� es eine kurze Zeitverz�gerung zwischen dem Abspielen der T�ne im Programm und dem erreichen deiner Lautsprecher gibt (Also dem H�ren). Audacity berichtigt diese kurze Zeitverz�gerung nicht automatisch, da� musst du manuell machen.

Um dies zu tun, benutze das "Timeshift" Modul von Audacity und verschiebe eine der beiden Spuren, bis sie synchron sind. Dies kannst du tun, w�hrend du das ganze anh�rst.

<p>

<a name="a4"></a>
<font size=+1><b>
4. Warum wird Audacity nicht mit einem MP3 encoder ausgeliefert?
</b></font>

<p>
Leider ist der Algorythmus zur Codierung und Decodierung von MP3's patentiert.
Audacity kann keinen MP3 Algorythmus beinhalten, ohne Geb�hren zu bezahlen oder sich
in vielen L�ndern strafbar zu machen.

<p>
Als Kompromiss wurde die M�glichkeit, externe Encoder zu verwenden, eingebaut.
Die Encoder m�ssen separat geladen werden und es liegt an Ihnen,
ob Sie deren Lizenzbestimmungen akzepieren wollen.

<a href="#a5"></a>
<font size=+1><b>
5. Kann man RealAudio oder anderes "gestreamte Audio" aufnehmen ?<br><p>
</b></font>
Eigentlich nicht. Die meiste Musik , die gestreamt wird, auch die die f�r den RealOne Player, Windows Media Player oder Quicktime geliefert wird, soll eigentlich verhindern, dass du diese aufnehmen kannst.
<p>
Aber es ist immer noch m&ouml;glich alles, was du auf deinem Computer abspielen kannst, auch aufzunehmen. Verbinde dazu nur deinen Outputkanal an der Soundkarte (in der Regel der gr�ne Ausgang) mit dem Line In Eingang deiner Soundkarte. Benutzte dazu ein 1/8 Inch Audio Stereo Kabel.
<p>
Wenn du dies so gemacht hast, kann Audacity alles aufnehmen, was abgespielt wird. Dr&uuml;cke dazu erst den Aufnahmeknopf in Audacity, danach den �Start� Knopf in deiner Anwendung und Audacity nimmt alles auf ! (vgl. auch die n&auml;chste Frage).



<p>
<a href="#a6"></a>
<font size=+1><b>
6. Hilfe! Ich dr�cke Aufnahme, aber alles was ich bekomme ist "Stille"!</b></font>
<br>
<p>
Audacity benutzt zur Aufnahme den Standard Input, der in deinem Betriebssystem festgelegt ist. Wenn man mehrere M&ouml;glichkeiten hat, Aufnahmen zu starten, kann , bei einer falschen Wahl, Audacity nur �Stille� aufnehmen.
Ein Beispiel: Du hast ein Mikrofon angeschlossen und hast aber im Input den Line In Eingang gew&auml;hlt. Dann kommt nichts an und Audacity kann auch nichts aufnehmen.
<p>
Wenn du Windows benutzt, kann du mit Rechts-Klick auf das Lautst&auml;rke-Symbol (Rechts unten) den Input-Kanal w&auml;hlen.
<p>
Wenn du Mac OS9 besitzt, geht dies &uuml;ber die Sound Control. Wenn du Mac OSX benutzt, gehe &uuml;ber die Sound Control in den Systemeinstellungen (Bei 10.2 oder h&ouml;her ist dies ein eigener Reiter).

<p>
<a href="#a7"></a>
<font size=+1><b>
7. Wie trenne ich ein Lied (Track) in verschiedene St�cke ?</b></font><br>
<p>
in �bersetzung
<p>
<a href="#a8"></a>
<font size=+1><b>
8. Wie bekomme ich die Lieder von einer Audio CD ?</b></font><br>
<p>
in �bersetzung
<p>
<p>
F�r n�here Informationen lesen Sie in unserer Online Hilfe nach.


<?php BoxBottom(); ?>
