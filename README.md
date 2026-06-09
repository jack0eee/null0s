null0s

Un kernel minimale per avviare
direttamente su una macchina senza altro 
Sistema Operativo un emulazione Z80
per far girare e rivivere una ZX81
su qualsiasi hardware i686

Tutto il software viene rilasciato con licenza GNU GPL v3
di Free Software Foundation

Autore Angelo Raffaele Granito (jack0e)

Copyleft 2026

-------

Istruzione per il build :

Con OperBSD viene compilato con clang, va istallato 
solamente grub per poter creare la ISO.

Per la build completa eseguire :

tar xfvz null0s-0.1.tar.gz
cd null0s 
./build.OpenBSD.sh


Per avviarlo con qemu

Bisogna installare qemu

arcadia$ doas pkg_add grub
quirks-7.147 signed on 2025-10-10T23:15:26Z
Can't find grub
arcadia$ doas pkg_info -Q grub
arcadia$ doas pkg_add qemu     
quirks-7.147 signed on 2025-10-10T23:15:26Z
qemu-10.0.2:capstone-5.0: ok
qemu-10.0.2:dtc-1.7.0: ok
qemu-10.0.2:libiscsi-1.20.0: ok
qemu-10.0.2:libnfs-5.0.2: ok
qemu-10.0.2:libtasn1-4.20.0p0: ok
qemu-10.0.2:p11-kit-0.25.10p0: ok
qemu-10.0.2:libunistring-0.9.7: ok
qemu-10.0.2:libidn2-2.3.0p0: ok
qemu-10.0.2:libunbound-1.24.2: ok
qemu-10.0.2:libnettle-3.10.2: ok
qemu-10.0.2:brotli-1.0.9p1: ok
qemu-10.0.2:gnutls-3.8.10p1: ok
qemu-10.0.2:vte3-common-0.80.4: ok
qemu-10.0.2:vte3-0.80.4: ok
qemu-10.0.2:libslirp-4.7.0: ok
qemu-10.0.2:qemu-ga-10.0.2: ok
qemu-10.0.2:libssh-0.11.3: ok
qemu-10.0.2: ok
Running tags: ok
The following new rcscripts were installed: /etc/rc.d/qemu_ga
See rcctl(8) for details.
New and changed readme(s):
        /usr/local/share/doc/pkg-readmes/qemu
        /usr/local/share/doc/pkg-readmes/qemu-ga


null0s e' un kernel multiboot (GRUB ecosystem)
ma grub non e' presente ufficialmente perche'
per i progettisti di OpenBSD e' insicuro ed invogliano
il non utilizzo.

VMM non e' facilmente utilizzabile perche' non carica 
kernel raw a ELF32 e richieste dischi virtuali bootabili
(tipo ISO o OS completo)

mentre la ISO potrebbe fargli fare il boot.

--------------
qemu-system-i386 -kernel null0s.bin

grub-mkrescue -o null0s.iso iso

qemu-system-i386 -cdrom null0s.iso



 
