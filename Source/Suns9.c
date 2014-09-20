#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	char name[100];
	char rootfs[50];
	char rootfskey[100];
	char kette[200];
	char a=0;
	if(argc<=3) {
		printf("Usage: Suns9 7.1.2-ipsw target-ipsw's-rootfs target-ipsw's-rootfs-key\n");
		return;
	}

	strcpy(name,argv[1]);
	strcat(name,".zip");

	strcpy(rootfs,argv[2]);

	strcpy(rootfskey,argv[3]);

	//renaming the ipsw
	rename(argv[1],"iOS-7.1.2.ipsw");
	strcpy(argv[1],"iOS-7.1.2.ipsw");
	strcpy(name,"iOS-7.1.2.ipsw.zip");

	strcpy(kette,"MOVE ");
	strcat(kette,argv[1]);
	strcat(kette," Suns9-files");
	system(kette);

	strcpy(kette,"MOVE ");
	strcat(kette,rootfs);
	strcat(kette," Suns9-files");
	system(kette);
	chdir("Suns9-files");


	//renaming the ipsw file into *.ipsw.zip
	strcpy(kette,"RENAME ");
	strcat(kette,argv[1]);
	strcat(kette," ");
	strcat(kette,name);
	system(kette);

	a=0;
	//extracting iBSS for iPhone3,1
	strcpy(kette,"7z e ");
	strcat(kette,name);
	strcat(kette," Firmware\\dfu\\iBSS.n90ap.RELEASE.dfu");
	system(kette);
	if(access("iBSS.n90ap.RELEASE.dfu",0)==0) {
		
		a=1;
		//exctracting iBEC
		strcpy(kette,"7z e ");
		strcat(kette,name);
		strcat(kette," Firmware\\dfu\\iBEC.n90ap.RELEASE.dfu");
		system(kette);

		//extracting restore ramdisk
		strcpy(kette,"7z e ");
		strcat(kette,name);
		strcat(kette," 058-4107-013.dmg");
		system(kette);
		
		//patching iBSS
		system("bspatch iBSS.n90ap.RELEASE.dfu iBSS.n90ap.RELEASE.dfu.pwned tethered-downgrade-patches\\iPhone3,1-iBSS.patch");
		system("DEL iBSS.n90ap.RELEASE.dfu");
		system("RENAME iBSS.n90ap.RELEASE.dfu.pwned iBSS.n90ap.RELEASE.dfu");
		
		//patching iBEC
		system("bspatch iBEC.n90ap.RELEASE.dfu iBEC.n90ap.RELEASE.dfu.pwned tethered-downgrade-patches\\iPhone3,1-iBEC.patch");
		system("DEL iBEC.n90ap.RELEASE.dfu");
		system("RENAME iBEC.n90ap.RELEASE.dfu.pwned iBEC.n90ap.RELEASE.dfu");

		//decrypting rootfs
		strcpy(kette,"dmg extract ");
		strcat(kette,rootfs);
		strcat(kette," 058-4520-010-ex.dmg -k ");
		strcat(kette,rootfskey);
		system(kette);

		//compressing and hashing rootfs
		system("dmg build 058-4520-010-ex.dmg 058-4520-010.dmg");

		//deleting unnecessary rootfs files
		system("DEL 058-4520-010-ex.dmg");
		strcpy(kette,"DEL ");
		strcat(kette,rootfs);
		system(kette);

		//patching ramdisk
		system("xpwntool 058-4107-013.dmg 058-4107-013.dmg.dec -k 23582ce84d0149c1819b72948c6a55a155c1fa4366678a9e51a6f66f5a77de10 -iv 4bd50f8abb89925f20793baac84ad76b");

		system("hfsplus 058-4107-013.dmg.dec extract /usr/sbin/asr asr.hex");
		system("bspatch asr.hex asr-patched.hex tethered-downgrade-patches\\iPhone3,1-asr.patch");
		system("hfsplus 058-4107-013.dmg.dec grow 10000000");
		system("hfsplus 058-4107-013.dmg.dec mv /usr/sbin/asr /usr/sbin/asr_orig");
		system("hfsplus 058-4107-013.dmg.dec add asr-patched.hex /usr/sbin/asr");
		system("hfsplus 058-4107-013.dmg.dec chmod 100755 /usr/sbin/asr");

		system("xpwntool 058-4107-013.dmg.dec 058-4107-013.dmg.pwned -t 058-4107-013.dmg -k 23582ce84d0149c1819b72948c6a55a155c1fa4366678a9e51a6f66f5a77de10 -iv 4bd50f8abb89925f20793baac84ad76b");
		system("DEL 058-4107-013.dmg 058-4107-013.dmg.dec asr.hex asr-patched.hex");
		system("RENAME 058-4107-013.dmg.pwned 058-4107-013.dmg");
		system("MKDIR Firmware");
		chdir("Firmware");
		system("MKDIR dfu");
		system("MOVE ..\\iBSS.n90ap.RELEASE.dfu dfu");
		system("MOVE ..\\iBEC.n90ap.RELEASE.dfu dfu");
		chdir("..");
		strcpy(kette,"7z u ");
		strcat(kette,name);
		strcat(kette," Firmware\\dfu\\iBSS.n90ap.RELEASE.dfu Firmware\\dfu\\iBEC.n90ap.RELEASE.dfu 058-4107-013.dmg 058-4520-010.dmg");
		system(kette);
		system("DEL 058-4107-013.dmg");
		system("DEL 058-4520-010.dmg");
		strcpy(kette,"RENAME ");
		strcat(kette,name);
		strcat(kette," ");
		strcat(kette,"Suns9-tethered-downgrade-n90ap.ipsw");
		system(kette);
		chdir("Firmware\\dfu");
		system("DEL iBSS.n90ap.RELEASE.dfu iBEC.n90ap.RELEASE.dfu");
		chdir("..");
		system("RMDIR dfu");
		chdir("..");
		system("RMDIR Firmware");
		strcpy(kette,"MOVE Suns9-tethered-downgrade-n90ap.ipsw ..");
		system(kette);
	}








	if(a==0) {

	//extracting iBSS for iPhone3,3
	strcpy(kette,"7z e ");
	strcat(kette,name);
	strcat(kette," Firmware\\dfu\\iBSS.n92ap.RELEASE.dfu");
	system(kette);
	if(access("iBSS.n92ap.RELEASE.dfu",0)==0) {
		
		a=1;
		//exctracting iBEC
		strcpy(kette,"7z e ");
		strcat(kette,name);
		strcat(kette," Firmware\\dfu\\iBEC.n92ap.RELEASE.dfu");
		system(kette);

		//extracting restore ramdisk
		strcpy(kette,"7z e ");
		strcat(kette,name);
		strcat(kette," 058-4107-013.dmg");
		system(kette);
		
		//patching iBSS
		system("bspatch iBSS.n92ap.RELEASE.dfu iBSS.n92ap.RELEASE.dfu.pwned tethered-downgrade-patches\\iPhone3,3-iBSS.patch");
		system("DEL iBSS.n92ap.RELEASE.dfu");
		system("RENAME iBSS.n92ap.RELEASE.dfu.pwned iBSS.n92ap.RELEASE.dfu");
		
		//patching iBEC
		system("bspatch iBEC.n92ap.RELEASE.dfu iBEC.n92ap.RELEASE.dfu.pwned tethered-downgrade-patches\\iPhone3,3-iBEC.patch");
		system("DEL iBEC.n92ap.RELEASE.dfu");
		system("RENAME iBEC.n92ap.RELEASE.dfu.pwned iBEC.n92ap.RELEASE.dfu");

		//decrypting rootfs
		strcpy(kette,"dmg extract ");
		strcat(kette,rootfs);
		strcat(kette," 058-4110-009-ex.dmg -k ");
		strcat(kette,rootfskey);
		system(kette);

		//compressing and hashing rootfs
		system("dmg build 058-4110-009-ex.dmg 058-4110-009.dmg");

		//deleting unnecessary rootfs files
		system("DEL 058-4110-009-ex.dmg");
		strcpy(kette,"DEL ");
		strcat(kette,rootfs);
		system(kette);

		//patching ramdisk
		system("xpwntool 058-4107-013.dmg 058-4107-013.dmg.dec -k ad5cfa520f1018d4083710011f627107389785f425303938e5412dff1aee65bb -iv e6562294eb9989aaca7fda5b57065fde");

		system("hfsplus 058-4107-013.dmg.dec extract /usr/sbin/asr asr.hex");
		system("bspatch asr.hex asr-patched.hex tethered-downgrade-patches\\iPhone3,3-asr.patch");
		system("hfsplus 058-4107-013.dmg.dec grow 10000000");
		system("hfsplus 058-4107-013.dmg.dec mv /usr/sbin/asr /usr/sbin/asr_orig");
		system("hfsplus 058-4107-013.dmg.dec add asr-patched.hex /usr/sbin/asr");
		system("hfsplus 058-4107-013.dmg.dec chmod 100755 /usr/sbin/asr");

		system("xpwntool 058-4107-013.dmg.dec 058-4107-013.dmg.pwned -t 058-4107-013.dmg -k ad5cfa520f1018d4083710011f627107389785f425303938e5412dff1aee65bb -iv e6562294eb9989aaca7fda5b57065fde");
		system("DEL 058-4107-013.dmg 058-4107-013.dmg.dec asr.hex asr-patched.hex");
		system("RENAME 058-4107-013.dmg.pwned 058-4107-013.dmg");
		system("MKDIR Firmware");
		chdir("Firmware");
		system("MKDIR dfu");
		system("MOVE ..\\iBSS.n92ap.RELEASE.dfu dfu");
		system("MOVE ..\\iBEC.n92ap.RELEASE.dfu dfu");
		chdir("..");
		strcpy(kette,"7z u ");
		strcat(kette,name);
		strcat(kette," Firmware\\dfu\\iBSS.n92ap.RELEASE.dfu Firmware\\dfu\\iBEC.n92ap.RELEASE.dfu 058-4107-013.dmg 058-4110-009.dmg");
		system(kette);
		system("DEL 058-4110-009.dmg");
		system("DEL 058-4107-013.dmg");
		strcpy(kette,"RENAME ");
		strcat(kette,name);
		strcat(kette," ");
		strcat(kette,"Suns9-tethered-downgrade-n92ap.ipsw");
		system(kette);
		chdir("Firmware\\dfu");
		system("DEL iBSS.n92ap.RELEASE.dfu iBEC.n92ap.RELEASE.dfu");
		chdir("..");
		system("RMDIR dfu");
		chdir("..");
		system("RMDIR Firmware");
		strcpy(kette,"MOVE Suns9-tethered-downgrade-n92ap.ipsw ..");
		system(kette);
	}
	}


	if(a==0) {

	//extracting iBSS for iPhone3,2
	strcpy(kette,"7z e ");
	strcat(kette,name);
	strcat(kette," Firmware\\dfu\\iBSS.n90bap.RELEASE.dfu");
	system(kette);
	if(access("iBSS.n90bap.RELEASE.dfu",0)==0) {

		//exctracting iBEC
		strcpy(kette,"7z e ");
		strcat(kette,name);
		strcat(kette," Firmware\\dfu\\iBEC.n90bap.RELEASE.dfu");
		system(kette);

		//extracting restore ramdisk
		strcpy(kette,"7z e ");
		strcat(kette,name);
		strcat(kette," 058-4107-013.dmg");
		system(kette);
		
		//patching iBSS
		system("bspatch iBSS.n90bap.RELEASE.dfu iBSS.n90bap.RELEASE.dfu.pwned tethered-downgrade-patches\\iPhone3,2-iBSS.patch");
		system("DEL iBSS.n90bap.RELEASE.dfu");
		system("RENAME iBSS.n90bap.RELEASE.dfu.pwned iBSS.n90bap.RELEASE.dfu");
		
		//patching iBEC
		system("bspatch iBEC.n90bap.RELEASE.dfu iBEC.n90bap.RELEASE.dfu.pwned tethered-downgrade-patches\\iPhone3,2-iBEC.patch");
		system("DEL iBEC.n90bap.RELEASE.dfu");
		system("RENAME iBEC.n90bap.RELEASE.dfu.pwned iBEC.n90bap.RELEASE.dfu");

		//decrypting rootfs
		strcpy(kette,"dmg extract ");
		strcat(kette,rootfs);
		strcat(kette," 058-4498-010-ex.dmg -k ");
		strcat(kette,rootfskey);
		system(kette);

		//compressing and hashing rootfs
		system("dmg build 058-4498-010-ex.dmg 058-4498-010.dmg");

		//deleting unnecessary rootfs files
		system("DEL 058-4498-010-ex.dmg");
		strcpy(kette,"DEL ");
		strcat(kette,rootfs);
		system(kette);

		//patching ramdisk
		system("xpwntool 058-4107-013.dmg 058-4107-013.dmg.dec -k 2ab11294614e2fda8e8c806208e3bd96337877673e166702e5f5df558da48b09 -iv 4d45b18575f0e48ef0c1f1fea1663e0e");

		system("hfsplus 058-4107-013.dmg.dec extract /usr/sbin/asr asr.hex");
		system("bspatch asr.hex asr-patched.hex tethered-downgrade-patches\\iPhone3,2-asr.patch");
		system("hfsplus 058-4107-013.dmg.dec grow 10000000");
		system("hfsplus 058-4107-013.dmg.dec mv /usr/sbin/asr /usr/sbin/asr_orig");
		system("hfsplus 058-4107-013.dmg.dec add asr-patched.hex /usr/sbin/asr");
		system("hfsplus 058-4107-013.dmg.dec chmod 100755 /usr/sbin/asr");

		system("xpwntool 058-4107-013.dmg.dec 058-4107-013.dmg.pwned -t 058-4107-013.dmg -k 2ab11294614e2fda8e8c806208e3bd96337877673e166702e5f5df558da48b09 -iv 4d45b18575f0e48ef0c1f1fea1663e0e");
		system("DEL 058-4107-013.dmg 058-4107-013.dmg.dec asr.hex asr-patched.hex");
		system("RENAME 058-4107-013.dmg.pwned 058-4107-013.dmg");
		system("MKDIR Firmware");
		chdir("Firmware");
		system("MKDIR dfu");
		system("MOVE ..\\iBSS.n90bap.RELEASE.dfu dfu");
		system("MOVE ..\\iBEC.n90bap.RELEASE.dfu dfu");
		chdir("..");
		strcpy(kette,"7z u ");
		strcat(kette,name);
		strcat(kette," Firmware\\dfu\\iBSS.n90bap.RELEASE.dfu Firmware\\dfu\\iBEC.n90bap.RELEASE.dfu 058-4107-013.dmg 058-4498-010.dmg");
		system(kette);
		system("DEL 058-4498-010.dmg");
		system("DEL 058-4107-013.dmg");
		strcpy(kette,"RENAME ");
		strcat(kette,name);
		strcat(kette," ");
		strcat(kette,"Suns9-tethered-downgrade-n90bap.ipsw");
		system(kette);
		chdir("Firmware\\dfu");
		system("DEL iBSS.n90bap.RELEASE.dfu iBEC.n90bap.RELEASE.dfu");
		chdir("..");
		system("RMDIR dfu");
		chdir("..");
		system("RMDIR Firmware");
		strcpy(kette,"MOVE Suns9-tethered-downgrade-n90bap.ipsw ..");
		system(kette);
	}
	}



}