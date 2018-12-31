@if %1 == ? (echo on)

@if %1 == b  (jom -j 4)

@if %1 == c  (configure -opensource -confirm-license -debug -shared -fast -no-qt3support)

@if %1 == cb (configure -opensource -confirm-license -debug -shared -fast -no-qt3support && jom -j 4)

@rem -no-3dnow -no-openssl -no-dbus -no-phonon -no-phonon-backend -no-multimedia -no-audio-backend -no-script -no-scripttools -no-webkit -no-directwrite -no-nis -no-cups -no-iconv -no-neon -no-fontconfig -no-opengl -no-xmlpatterns