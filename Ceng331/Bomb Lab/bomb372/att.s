
bomb:     file format elf64-x86-64


Disassembly of section .init:

0000000000400b38 <_init>:
  400b38:	48 83 ec 08          	sub    $0x8,%rsp
  400b3c:	48 8b 05 b5 34 20 00 	mov    0x2034b5(%rip),%rax        # 603ff8 <__gmon_start__>
  400b43:	48 85 c0             	test   %rax,%rax
  400b46:	74 05                	je     400b4d <_init+0x15>
  400b48:	e8 f3 01 00 00       	callq  400d40 <__gmon_start__@plt>
  400b4d:	48 83 c4 08          	add    $0x8,%rsp
  400b51:	c3                   	retq   

Disassembly of section .plt:

0000000000400b60 <.plt>:
  400b60:	ff 35 a2 34 20 00    	pushq  0x2034a2(%rip)        # 604008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400b66:	ff 25 a4 34 20 00    	jmpq   *0x2034a4(%rip)        # 604010 <_GLOBAL_OFFSET_TABLE_+0x10>
  400b6c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400b70 <__strcat_chk@plt>:
  400b70:	ff 25 a2 34 20 00    	jmpq   *0x2034a2(%rip)        # 604018 <__strcat_chk@GLIBC_2.3.4>
  400b76:	68 00 00 00 00       	pushq  $0x0
  400b7b:	e9 e0 ff ff ff       	jmpq   400b60 <.plt>

0000000000400b80 <getenv@plt>:
  400b80:	ff 25 9a 34 20 00    	jmpq   *0x20349a(%rip)        # 604020 <getenv@GLIBC_2.2.5>
  400b86:	68 01 00 00 00       	pushq  $0x1
  400b8b:	e9 d0 ff ff ff       	jmpq   400b60 <.plt>

0000000000400b90 <strcasecmp@plt>:
  400b90:	ff 25 92 34 20 00    	jmpq   *0x203492(%rip)        # 604028 <strcasecmp@GLIBC_2.2.5>
  400b96:	68 02 00 00 00       	pushq  $0x2
  400b9b:	e9 c0 ff ff ff       	jmpq   400b60 <.plt>

0000000000400ba0 <__errno_location@plt>:
  400ba0:	ff 25 8a 34 20 00    	jmpq   *0x20348a(%rip)        # 604030 <__errno_location@GLIBC_2.2.5>
  400ba6:	68 03 00 00 00       	pushq  $0x3
  400bab:	e9 b0 ff ff ff       	jmpq   400b60 <.plt>

0000000000400bb0 <strcpy@plt>:
  400bb0:	ff 25 82 34 20 00    	jmpq   *0x203482(%rip)        # 604038 <strcpy@GLIBC_2.2.5>
  400bb6:	68 04 00 00 00       	pushq  $0x4
  400bbb:	e9 a0 ff ff ff       	jmpq   400b60 <.plt>

0000000000400bc0 <puts@plt>:
  400bc0:	ff 25 7a 34 20 00    	jmpq   *0x20347a(%rip)        # 604040 <puts@GLIBC_2.2.5>
  400bc6:	68 05 00 00 00       	pushq  $0x5
  400bcb:	e9 90 ff ff ff       	jmpq   400b60 <.plt>

0000000000400bd0 <write@plt>:
  400bd0:	ff 25 72 34 20 00    	jmpq   *0x203472(%rip)        # 604048 <write@GLIBC_2.2.5>
  400bd6:	68 06 00 00 00       	pushq  $0x6
  400bdb:	e9 80 ff ff ff       	jmpq   400b60 <.plt>

0000000000400be0 <__stack_chk_fail@plt>:
  400be0:	ff 25 6a 34 20 00    	jmpq   *0x20346a(%rip)        # 604050 <__stack_chk_fail@GLIBC_2.4>
  400be6:	68 07 00 00 00       	pushq  $0x7
  400beb:	e9 70 ff ff ff       	jmpq   400b60 <.plt>

0000000000400bf0 <alarm@plt>:
  400bf0:	ff 25 62 34 20 00    	jmpq   *0x203462(%rip)        # 604058 <alarm@GLIBC_2.2.5>
  400bf6:	68 08 00 00 00       	pushq  $0x8
  400bfb:	e9 60 ff ff ff       	jmpq   400b60 <.plt>

0000000000400c00 <close@plt>:
  400c00:	ff 25 5a 34 20 00    	jmpq   *0x20345a(%rip)        # 604060 <close@GLIBC_2.2.5>
  400c06:	68 09 00 00 00       	pushq  $0x9
  400c0b:	e9 50 ff ff ff       	jmpq   400b60 <.plt>

0000000000400c10 <read@plt>:
  400c10:	ff 25 52 34 20 00    	jmpq   *0x203452(%rip)        # 604068 <read@GLIBC_2.2.5>
  400c16:	68 0a 00 00 00       	pushq  $0xa
  400c1b:	e9 40 ff ff ff       	jmpq   400b60 <.plt>

0000000000400c20 <__libc_start_main@plt>:
  400c20:	ff 25 4a 34 20 00    	jmpq   *0x20344a(%rip)        # 604070 <__libc_start_main@GLIBC_2.2.5>
  400c26:	68 0b 00 00 00       	pushq  $0xb
  400c2b:	e9 30 ff ff ff       	jmpq   400b60 <.plt>

0000000000400c30 <fgets@plt>:
  400c30:	ff 25 42 34 20 00    	jmpq   *0x203442(%rip)        # 604078 <fgets@GLIBC_2.2.5>
  400c36:	68 0c 00 00 00       	pushq  $0xc
  400c3b:	e9 20 ff ff ff       	jmpq   400b60 <.plt>

0000000000400c40 <signal@plt>:
  400c40:	ff 25 3a 34 20 00    	jmpq   *0x20343a(%rip)        # 604080 <signal@GLIBC_2.2.5>
  400c46:	68 0d 00 00 00       	pushq  $0xd
  400c4b:	e9 10 ff ff ff       	jmpq   400b60 <.plt>

0000000000400c50 <gethostbyname@plt>:
  400c50:	ff 25 32 34 20 00    	jmpq   *0x203432(%rip)        # 604088 <gethostbyname@GLIBC_2.2.5>
  400c56:	68 0e 00 00 00       	pushq  $0xe
  400c5b:	e9 00 ff ff ff       	jmpq   400b60 <.plt>

0000000000400c60 <__memmove_chk@plt>:
  400c60:	ff 25 2a 34 20 00    	jmpq   *0x20342a(%rip)        # 604090 <__memmove_chk@GLIBC_2.3.4>
  400c66:	68 0f 00 00 00       	pushq  $0xf
  400c6b:	e9 f0 fe ff ff       	jmpq   400b60 <.plt>

0000000000400c70 <strtol@plt>:
  400c70:	ff 25 22 34 20 00    	jmpq   *0x203422(%rip)        # 604098 <strtol@GLIBC_2.2.5>
  400c76:	68 10 00 00 00       	pushq  $0x10
  400c7b:	e9 e0 fe ff ff       	jmpq   400b60 <.plt>

0000000000400c80 <fflush@plt>:
  400c80:	ff 25 1a 34 20 00    	jmpq   *0x20341a(%rip)        # 6040a0 <fflush@GLIBC_2.2.5>
  400c86:	68 11 00 00 00       	pushq  $0x11
  400c8b:	e9 d0 fe ff ff       	jmpq   400b60 <.plt>

0000000000400c90 <__isoc99_sscanf@plt>:
  400c90:	ff 25 12 34 20 00    	jmpq   *0x203412(%rip)        # 6040a8 <__isoc99_sscanf@GLIBC_2.7>
  400c96:	68 12 00 00 00       	pushq  $0x12
  400c9b:	e9 c0 fe ff ff       	jmpq   400b60 <.plt>

0000000000400ca0 <__printf_chk@plt>:
  400ca0:	ff 25 0a 34 20 00    	jmpq   *0x20340a(%rip)        # 6040b0 <__printf_chk@GLIBC_2.3.4>
  400ca6:	68 13 00 00 00       	pushq  $0x13
  400cab:	e9 b0 fe ff ff       	jmpq   400b60 <.plt>

0000000000400cb0 <fopen@plt>:
  400cb0:	ff 25 02 34 20 00    	jmpq   *0x203402(%rip)        # 6040b8 <fopen@GLIBC_2.2.5>
  400cb6:	68 14 00 00 00       	pushq  $0x14
  400cbb:	e9 a0 fe ff ff       	jmpq   400b60 <.plt>

0000000000400cc0 <gethostname@plt>:
  400cc0:	ff 25 fa 33 20 00    	jmpq   *0x2033fa(%rip)        # 6040c0 <gethostname@GLIBC_2.2.5>
  400cc6:	68 15 00 00 00       	pushq  $0x15
  400ccb:	e9 90 fe ff ff       	jmpq   400b60 <.plt>

0000000000400cd0 <exit@plt>:
  400cd0:	ff 25 f2 33 20 00    	jmpq   *0x2033f2(%rip)        # 6040c8 <exit@GLIBC_2.2.5>
  400cd6:	68 16 00 00 00       	pushq  $0x16
  400cdb:	e9 80 fe ff ff       	jmpq   400b60 <.plt>

0000000000400ce0 <connect@plt>:
  400ce0:	ff 25 ea 33 20 00    	jmpq   *0x2033ea(%rip)        # 6040d0 <connect@GLIBC_2.2.5>
  400ce6:	68 17 00 00 00       	pushq  $0x17
  400ceb:	e9 70 fe ff ff       	jmpq   400b60 <.plt>

0000000000400cf0 <__fprintf_chk@plt>:
  400cf0:	ff 25 e2 33 20 00    	jmpq   *0x2033e2(%rip)        # 6040d8 <__fprintf_chk@GLIBC_2.3.4>
  400cf6:	68 18 00 00 00       	pushq  $0x18
  400cfb:	e9 60 fe ff ff       	jmpq   400b60 <.plt>

0000000000400d00 <sleep@plt>:
  400d00:	ff 25 da 33 20 00    	jmpq   *0x2033da(%rip)        # 6040e0 <sleep@GLIBC_2.2.5>
  400d06:	68 19 00 00 00       	pushq  $0x19
  400d0b:	e9 50 fe ff ff       	jmpq   400b60 <.plt>

0000000000400d10 <__ctype_b_loc@plt>:
  400d10:	ff 25 d2 33 20 00    	jmpq   *0x2033d2(%rip)        # 6040e8 <__ctype_b_loc@GLIBC_2.3>
  400d16:	68 1a 00 00 00       	pushq  $0x1a
  400d1b:	e9 40 fe ff ff       	jmpq   400b60 <.plt>

0000000000400d20 <__sprintf_chk@plt>:
  400d20:	ff 25 ca 33 20 00    	jmpq   *0x2033ca(%rip)        # 6040f0 <__sprintf_chk@GLIBC_2.3.4>
  400d26:	68 1b 00 00 00       	pushq  $0x1b
  400d2b:	e9 30 fe ff ff       	jmpq   400b60 <.plt>

0000000000400d30 <socket@plt>:
  400d30:	ff 25 c2 33 20 00    	jmpq   *0x2033c2(%rip)        # 6040f8 <socket@GLIBC_2.2.5>
  400d36:	68 1c 00 00 00       	pushq  $0x1c
  400d3b:	e9 20 fe ff ff       	jmpq   400b60 <.plt>

Disassembly of section .plt.got:

0000000000400d40 <__gmon_start__@plt>:
  400d40:	ff 25 b2 32 20 00    	jmpq   *0x2032b2(%rip)        # 603ff8 <__gmon_start__>
  400d46:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000400d50 <_start>:
  400d50:	31 ed                	xor    %ebp,%ebp
  400d52:	49 89 d1             	mov    %rdx,%r9
  400d55:	5e                   	pop    %rsi
  400d56:	48 89 e2             	mov    %rsp,%rdx
  400d59:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400d5d:	50                   	push   %rax
  400d5e:	54                   	push   %rsp
  400d5f:	49 c7 c0 30 26 40 00 	mov    $0x402630,%r8
  400d66:	48 c7 c1 c0 25 40 00 	mov    $0x4025c0,%rcx
  400d6d:	48 c7 c7 46 0e 40 00 	mov    $0x400e46,%rdi
  400d74:	e8 a7 fe ff ff       	callq  400c20 <__libc_start_main@plt>
  400d79:	f4                   	hlt    
  400d7a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400d80 <deregister_tm_clones>:
  400d80:	b8 87 47 60 00       	mov    $0x604787,%eax
  400d85:	55                   	push   %rbp
  400d86:	48 2d 80 47 60 00    	sub    $0x604780,%rax
  400d8c:	48 83 f8 0e          	cmp    $0xe,%rax
  400d90:	48 89 e5             	mov    %rsp,%rbp
  400d93:	76 1b                	jbe    400db0 <deregister_tm_clones+0x30>
  400d95:	b8 00 00 00 00       	mov    $0x0,%eax
  400d9a:	48 85 c0             	test   %rax,%rax
  400d9d:	74 11                	je     400db0 <deregister_tm_clones+0x30>
  400d9f:	5d                   	pop    %rbp
  400da0:	bf 80 47 60 00       	mov    $0x604780,%edi
  400da5:	ff e0                	jmpq   *%rax
  400da7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400dae:	00 00 
  400db0:	5d                   	pop    %rbp
  400db1:	c3                   	retq   
  400db2:	0f 1f 40 00          	nopl   0x0(%rax)
  400db6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400dbd:	00 00 00 

0000000000400dc0 <register_tm_clones>:
  400dc0:	be 80 47 60 00       	mov    $0x604780,%esi
  400dc5:	55                   	push   %rbp
  400dc6:	48 81 ee 80 47 60 00 	sub    $0x604780,%rsi
  400dcd:	48 c1 fe 03          	sar    $0x3,%rsi
  400dd1:	48 89 e5             	mov    %rsp,%rbp
  400dd4:	48 89 f0             	mov    %rsi,%rax
  400dd7:	48 c1 e8 3f          	shr    $0x3f,%rax
  400ddb:	48 01 c6             	add    %rax,%rsi
  400dde:	48 d1 fe             	sar    %rsi
  400de1:	74 15                	je     400df8 <register_tm_clones+0x38>
  400de3:	b8 00 00 00 00       	mov    $0x0,%eax
  400de8:	48 85 c0             	test   %rax,%rax
  400deb:	74 0b                	je     400df8 <register_tm_clones+0x38>
  400ded:	5d                   	pop    %rbp
  400dee:	bf 80 47 60 00       	mov    $0x604780,%edi
  400df3:	ff e0                	jmpq   *%rax
  400df5:	0f 1f 00             	nopl   (%rax)
  400df8:	5d                   	pop    %rbp
  400df9:	c3                   	retq   
  400dfa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400e00 <__do_global_dtors_aux>:
  400e00:	80 3d a1 39 20 00 00 	cmpb   $0x0,0x2039a1(%rip)        # 6047a8 <completed.7594>
  400e07:	75 11                	jne    400e1a <__do_global_dtors_aux+0x1a>
  400e09:	55                   	push   %rbp
  400e0a:	48 89 e5             	mov    %rsp,%rbp
  400e0d:	e8 6e ff ff ff       	callq  400d80 <deregister_tm_clones>
  400e12:	5d                   	pop    %rbp
  400e13:	c6 05 8e 39 20 00 01 	movb   $0x1,0x20398e(%rip)        # 6047a8 <completed.7594>
  400e1a:	f3 c3                	repz retq 
  400e1c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400e20 <frame_dummy>:
  400e20:	bf 20 3e 60 00       	mov    $0x603e20,%edi
  400e25:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  400e29:	75 05                	jne    400e30 <frame_dummy+0x10>
  400e2b:	eb 93                	jmp    400dc0 <register_tm_clones>
  400e2d:	0f 1f 00             	nopl   (%rax)
  400e30:	b8 00 00 00 00       	mov    $0x0,%eax
  400e35:	48 85 c0             	test   %rax,%rax
  400e38:	74 f1                	je     400e2b <frame_dummy+0xb>
  400e3a:	55                   	push   %rbp
  400e3b:	48 89 e5             	mov    %rsp,%rbp
  400e3e:	ff d0                	callq  *%rax
  400e40:	5d                   	pop    %rbp
  400e41:	e9 7a ff ff ff       	jmpq   400dc0 <register_tm_clones>

0000000000400e46 <main>:
  400e46:	53                   	push   %rbx
  400e47:	83 ff 01             	cmp    $0x1,%edi
  400e4a:	75 10                	jne    400e5c <main+0x16>
  400e4c:	48 8b 05 3d 39 20 00 	mov    0x20393d(%rip),%rax        # 604790 <stdin@@GLIBC_2.2.5>
  400e53:	48 89 05 56 39 20 00 	mov    %rax,0x203956(%rip)        # 6047b0 <infile>
  400e5a:	eb 63                	jmp    400ebf <main+0x79>
  400e5c:	48 89 f3             	mov    %rsi,%rbx
  400e5f:	83 ff 02             	cmp    $0x2,%edi
  400e62:	75 3a                	jne    400e9e <main+0x58>
  400e64:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
  400e68:	be de 2e 40 00       	mov    $0x402ede,%esi
  400e6d:	e8 3e fe ff ff       	callq  400cb0 <fopen@plt>
  400e72:	48 89 05 37 39 20 00 	mov    %rax,0x203937(%rip)        # 6047b0 <infile>
  400e79:	48 85 c0             	test   %rax,%rax
  400e7c:	75 41                	jne    400ebf <main+0x79>
  400e7e:	48 8b 4b 08          	mov    0x8(%rbx),%rcx
  400e82:	48 8b 13             	mov    (%rbx),%rdx
  400e85:	be 44 26 40 00       	mov    $0x402644,%esi
  400e8a:	bf 01 00 00 00       	mov    $0x1,%edi
  400e8f:	e8 0c fe ff ff       	callq  400ca0 <__printf_chk@plt>
  400e94:	bf 08 00 00 00       	mov    $0x8,%edi
  400e99:	e8 32 fe ff ff       	callq  400cd0 <exit@plt>
  400e9e:	48 8b 16             	mov    (%rsi),%rdx
  400ea1:	be 61 26 40 00       	mov    $0x402661,%esi
  400ea6:	bf 01 00 00 00       	mov    $0x1,%edi
  400eab:	b8 00 00 00 00       	mov    $0x0,%eax
  400eb0:	e8 eb fd ff ff       	callq  400ca0 <__printf_chk@plt>
  400eb5:	bf 08 00 00 00       	mov    $0x8,%edi
  400eba:	e8 11 fe ff ff       	callq  400cd0 <exit@plt>
  400ebf:	e8 a2 06 00 00       	callq  401566 <initialize_bomb>
  400ec4:	bf c8 26 40 00       	mov    $0x4026c8,%edi
  400ec9:	e8 f2 fc ff ff       	callq  400bc0 <puts@plt>
  400ece:	bf 08 27 40 00       	mov    $0x402708,%edi
  400ed3:	e8 e8 fc ff ff       	callq  400bc0 <puts@plt>
  400ed8:	e8 6b 09 00 00       	callq  401848 <read_line>
  400edd:	48 89 c7             	mov    %rax,%rdi
  400ee0:	e8 98 00 00 00       	callq  400f7d <phase_1>
  400ee5:	e8 84 0a 00 00       	callq  40196e <phase_defused>
  400eea:	bf 38 27 40 00       	mov    $0x402738,%edi
  400eef:	e8 cc fc ff ff       	callq  400bc0 <puts@plt>
  400ef4:	e8 4f 09 00 00       	callq  401848 <read_line>
  400ef9:	48 89 c7             	mov    %rax,%rdi
  400efc:	e8 04 01 00 00       	callq  401005 <phase_2>
  400f01:	e8 68 0a 00 00       	callq  40196e <phase_defused>
  400f06:	bf 7b 26 40 00       	mov    $0x40267b,%edi
  400f0b:	e8 b0 fc ff ff       	callq  400bc0 <puts@plt>
  400f10:	e8 33 09 00 00       	callq  401848 <read_line>
  400f15:	48 89 c7             	mov    %rax,%rdi
  400f18:	e8 4c 01 00 00       	callq  401069 <phase_3>
  400f1d:	e8 4c 0a 00 00       	callq  40196e <phase_defused>
  400f22:	bf 99 26 40 00       	mov    $0x402699,%edi
  400f27:	e8 94 fc ff ff       	callq  400bc0 <puts@plt>
  400f2c:	e8 17 09 00 00       	callq  401848 <read_line>
  400f31:	48 89 c7             	mov    %rax,%rdi
  400f34:	e8 24 02 00 00       	callq  40115d <phase_4>
  400f39:	e8 30 0a 00 00       	callq  40196e <phase_defused>
  400f3e:	bf 68 27 40 00       	mov    $0x402768,%edi
  400f43:	e8 78 fc ff ff       	callq  400bc0 <puts@plt>
  400f48:	e8 fb 08 00 00       	callq  401848 <read_line>
  400f4d:	48 89 c7             	mov    %rax,%rdi
  400f50:	e8 75 02 00 00       	callq  4011ca <phase_5>
  400f55:	e8 14 0a 00 00       	callq  40196e <phase_defused>
  400f5a:	bf a8 26 40 00       	mov    $0x4026a8,%edi
  400f5f:	e8 5c fc ff ff       	callq  400bc0 <puts@plt>
  400f64:	e8 df 08 00 00       	callq  401848 <read_line>
  400f69:	48 89 c7             	mov    %rax,%rdi
  400f6c:	e8 b6 02 00 00       	callq  401227 <phase_6>
  400f71:	e8 f8 09 00 00       	callq  40196e <phase_defused>
  400f76:	b8 00 00 00 00       	mov    $0x0,%eax
  400f7b:	5b                   	pop    %rbx
  400f7c:	c3                   	retq   

0000000000400f7d <phase_1>:
  400f7d:	53                   	push   %rbx
  400f7e:	48 83 ec 60          	sub    $0x60,%rsp
  400f82:	48 89 fb             	mov    %rdi,%rbx
  400f85:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400f8c:	00 00 
  400f8e:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
  400f93:	31 c0                	xor    %eax,%eax
  400f95:	48 b8 59 6f 75 72 20 	movabs $0x7865742072756f59,%rax
  400f9c:	74 65 78 
  400f9f:	48 89 04 24          	mov    %rax,(%rsp)
  400fa3:	48 b8 74 20 69 73 20 	movabs $0x2073692074,%rax
  400faa:	00 00 00 
  400fad:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  400fb2:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  400fb7:	b9 08 00 00 00       	mov    $0x8,%ecx
  400fbc:	b8 00 00 00 00       	mov    $0x0,%eax
  400fc1:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  400fc4:	ba 50 00 00 00       	mov    $0x50,%edx
  400fc9:	be 90 27 40 00       	mov    $0x402790,%esi
  400fce:	48 89 e7             	mov    %rsp,%rdi
  400fd1:	e8 9a fb ff ff       	callq  400b70 <__strcat_chk@plt>
  400fd6:	48 89 e6             	mov    %rsp,%rsi
  400fd9:	48 89 df             	mov    %rbx,%rdi
  400fdc:	e8 02 05 00 00       	callq  4014e3 <strings_not_equal>
  400fe1:	85 c0                	test   %eax,%eax
  400fe3:	74 05                	je     400fea <phase_1+0x6d>
  400fe5:	e8 e9 07 00 00       	callq  4017d3 <explode_bomb>
  400fea:	48 8b 44 24 58       	mov    0x58(%rsp),%rax
  400fef:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  400ff6:	00 00 
  400ff8:	74 05                	je     400fff <phase_1+0x82>
  400ffa:	e8 e1 fb ff ff       	callq  400be0 <__stack_chk_fail@plt>
  400fff:	48 83 c4 60          	add    $0x60,%rsp
  401003:	5b                   	pop    %rbx
  401004:	c3                   	retq   

0000000000401005 <phase_2>:
  401005:	55                   	push   %rbp
  401006:	53                   	push   %rbx
  401007:	48 83 ec 28          	sub    $0x28,%rsp
  40100b:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401012:	00 00 
  401014:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  401019:	31 c0                	xor    %eax,%eax
  40101b:	48 89 e6             	mov    %rsp,%rsi
  40101e:	e8 e6 07 00 00       	callq  401809 <read_six_numbers>
  401023:	48 89 e5             	mov    %rsp,%rbp
  401026:	bb 02 00 00 00       	mov    $0x2,%ebx
  40102b:	89 d8                	mov    %ebx,%eax
  40102d:	c1 e8 1f             	shr    $0x1f,%eax
  401030:	01 d8                	add    %ebx,%eax
  401032:	d1 f8                	sar    %eax
  401034:	03 45 04             	add    0x4(%rbp),%eax
  401037:	39 45 08             	cmp    %eax,0x8(%rbp)
  40103a:	74 05                	je     401041 <phase_2+0x3c>
  40103c:	e8 92 07 00 00       	callq  4017d3 <explode_bomb>
  401041:	83 c3 01             	add    $0x1,%ebx
  401044:	48 83 c5 04          	add    $0x4,%rbp
  401048:	83 fb 06             	cmp    $0x6,%ebx
  40104b:	75 de                	jne    40102b <phase_2+0x26>
  40104d:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  401052:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401059:	00 00 
  40105b:	74 05                	je     401062 <phase_2+0x5d>
  40105d:	e8 7e fb ff ff       	callq  400be0 <__stack_chk_fail@plt>
  401062:	48 83 c4 28          	add    $0x28,%rsp
  401066:	5b                   	pop    %rbx
  401067:	5d                   	pop    %rbp
  401068:	c3                   	retq   

0000000000401069 <phase_3>:
  401069:	48 83 ec 28          	sub    $0x28,%rsp
  40106d:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401074:	00 00 
  401076:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  40107b:	31 c0                	xor    %eax,%eax
  40107d:	4c 8d 44 24 14       	lea    0x14(%rsp),%r8
  401082:	48 8d 4c 24 10       	lea    0x10(%rsp),%rcx
  401087:	48 8d 54 24 0c       	lea    0xc(%rsp),%rdx
  40108c:	be aa 2a 40 00       	mov    $0x402aaa,%esi
  401091:	e8 fa fb ff ff       	callq  400c90 <__isoc99_sscanf@plt>
  401096:	83 f8 02             	cmp    $0x2,%eax
  401099:	7f 05                	jg     4010a0 <phase_3+0x37>
  40109b:	e8 33 07 00 00       	callq  4017d3 <explode_bomb>
  4010a0:	83 7c 24 0c 07       	cmpl   $0x7,0xc(%rsp)
  4010a5:	77 3c                	ja     4010e3 <phase_3+0x7a>
  4010a7:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  4010ab:	ff 24 c5 e0 27 40 00 	jmpq   *0x4027e0(,%rax,8)
  4010b2:	be 3d 01 00 00       	mov    $0x13d,%esi
  4010b7:	eb 3b                	jmp    4010f4 <phase_3+0x8b>
  4010b9:	be 54 02 00 00       	mov    $0x254,%esi
  4010be:	eb 34                	jmp    4010f4 <phase_3+0x8b>
  4010c0:	be 2a 02 00 00       	mov    $0x22a,%esi
  4010c5:	eb 2d                	jmp    4010f4 <phase_3+0x8b>
  4010c7:	be 9e 01 00 00       	mov    $0x19e,%esi
  4010cc:	eb 26                	jmp    4010f4 <phase_3+0x8b>
  4010ce:	be 10 01 00 00       	mov    $0x110,%esi
  4010d3:	eb 1f                	jmp    4010f4 <phase_3+0x8b>
  4010d5:	be ca 03 00 00       	mov    $0x3ca,%esi
  4010da:	eb 18                	jmp    4010f4 <phase_3+0x8b>
  4010dc:	be dd 01 00 00       	mov    $0x1dd,%esi
  4010e1:	eb 11                	jmp    4010f4 <phase_3+0x8b>
  4010e3:	e8 eb 06 00 00       	callq  4017d3 <explode_bomb>
  4010e8:	be 00 00 00 00       	mov    $0x0,%esi
  4010ed:	eb 05                	jmp    4010f4 <phase_3+0x8b>
  4010ef:	be a5 00 00 00       	mov    $0xa5,%esi
  4010f4:	8b 54 24 10          	mov    0x10(%rsp),%edx
  4010f8:	8b 7c 24 14          	mov    0x14(%rsp),%edi
  4010fc:	e8 8e 03 00 00       	callq  40148f <check_substraction_equal>
  401101:	85 c0                	test   %eax,%eax
  401103:	75 05                	jne    40110a <phase_3+0xa1>
  401105:	e8 c9 06 00 00       	callq  4017d3 <explode_bomb>
  40110a:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  40110f:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401116:	00 00 
  401118:	74 05                	je     40111f <phase_3+0xb6>
  40111a:	e8 c1 fa ff ff       	callq  400be0 <__stack_chk_fail@plt>
  40111f:	48 83 c4 28          	add    $0x28,%rsp
  401123:	c3                   	retq   

0000000000401124 <func4>:
  401124:	b8 00 00 00 00       	mov    $0x0,%eax
  401129:	83 ff 0a             	cmp    $0xa,%edi
  40112c:	7f 2d                	jg     40115b <func4+0x37>
  40112e:	89 f0                	mov    %esi,%eax
  401130:	83 ff 0a             	cmp    $0xa,%edi
  401133:	74 26                	je     40115b <func4+0x37>
  401135:	41 54                	push   %r12
  401137:	55                   	push   %rbp
  401138:	53                   	push   %rbx
  401139:	89 f5                	mov    %esi,%ebp
  40113b:	89 fb                	mov    %edi,%ebx
  40113d:	8d 7f 01             	lea    0x1(%rdi),%edi
  401140:	e8 df ff ff ff       	callq  401124 <func4>
  401145:	44 8d 64 05 00       	lea    0x0(%rbp,%rax,1),%r12d
  40114a:	8d 7b 02             	lea    0x2(%rbx),%edi
  40114d:	89 ee                	mov    %ebp,%esi
  40114f:	e8 d0 ff ff ff       	callq  401124 <func4>
  401154:	44 01 e0             	add    %r12d,%eax
  401157:	5b                   	pop    %rbx
  401158:	5d                   	pop    %rbp
  401159:	41 5c                	pop    %r12
  40115b:	f3 c3                	repz retq 

000000000040115d <phase_4>:
  40115d:	48 83 ec 18          	sub    $0x18,%rsp
  401161:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401168:	00 00 
  40116a:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  40116f:	31 c0                	xor    %eax,%eax
  401171:	48 89 e1             	mov    %rsp,%rcx
  401174:	48 8d 54 24 04       	lea    0x4(%rsp),%rdx
  401179:	be ad 2a 40 00       	mov    $0x402aad,%esi
  40117e:	e8 0d fb ff ff       	callq  400c90 <__isoc99_sscanf@plt>
  401183:	83 f8 02             	cmp    $0x2,%eax
  401186:	75 0b                	jne    401193 <phase_4+0x36>
  401188:	8b 04 24             	mov    (%rsp),%eax
  40118b:	83 e8 02             	sub    $0x2,%eax
  40118e:	83 f8 02             	cmp    $0x2,%eax
  401191:	76 05                	jbe    401198 <phase_4+0x3b>
  401193:	e8 3b 06 00 00       	callq  4017d3 <explode_bomb>
  401198:	8b 34 24             	mov    (%rsp),%esi
  40119b:	bf 05 00 00 00       	mov    $0x5,%edi
  4011a0:	e8 7f ff ff ff       	callq  401124 <func4>
  4011a5:	3b 44 24 04          	cmp    0x4(%rsp),%eax
  4011a9:	74 05                	je     4011b0 <phase_4+0x53>
  4011ab:	e8 23 06 00 00       	callq  4017d3 <explode_bomb>
  4011b0:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  4011b5:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4011bc:	00 00 
  4011be:	74 05                	je     4011c5 <phase_4+0x68>
  4011c0:	e8 1b fa ff ff       	callq  400be0 <__stack_chk_fail@plt>
  4011c5:	48 83 c4 18          	add    $0x18,%rsp
  4011c9:	c3                   	retq   

00000000004011ca <phase_5>:
  4011ca:	41 54                	push   %r12
  4011cc:	55                   	push   %rbp
  4011cd:	53                   	push   %rbx
  4011ce:	49 89 fc             	mov    %rdi,%r12
  4011d1:	e8 7f 02 00 00       	callq  401455 <string_length>
  4011d6:	83 f8 06             	cmp    $0x6,%eax
  4011d9:	74 05                	je     4011e0 <phase_5+0x16>
  4011db:	e8 f3 05 00 00       	callq  4017d3 <explode_bomb>
  4011e0:	49 8d 5c 24 01       	lea    0x1(%r12),%rbx
  4011e5:	49 83 c4 06          	add    $0x6,%r12
  4011e9:	0f be 3b             	movsbl (%rbx),%edi
  4011ec:	e8 59 03 00 00       	callq  40154a <from_char_to_int>
  4011f1:	89 c5                	mov    %eax,%ebp
  4011f3:	0f be 7b ff          	movsbl -0x1(%rbx),%edi
  4011f7:	e8 4e 03 00 00       	callq  40154a <from_char_to_int>
  4011fc:	83 e5 0f             	and    $0xf,%ebp
  4011ff:	89 c2                	mov    %eax,%edx
  401201:	83 e2 0f             	and    $0xf,%edx
  401204:	8b 04 95 20 28 40 00 	mov    0x402820(,%rdx,4),%eax
  40120b:	39 04 ad 20 28 40 00 	cmp    %eax,0x402820(,%rbp,4)
  401212:	7d 05                	jge    401219 <phase_5+0x4f>
  401214:	e8 ba 05 00 00       	callq  4017d3 <explode_bomb>
  401219:	48 83 c3 01          	add    $0x1,%rbx
  40121d:	4c 39 e3             	cmp    %r12,%rbx
  401220:	75 c7                	jne    4011e9 <phase_5+0x1f>
  401222:	5b                   	pop    %rbx
  401223:	5d                   	pop    %rbp
  401224:	41 5c                	pop    %r12
  401226:	c3                   	retq   

0000000000401227 <phase_6>:
  401227:	41 55                	push   %r13
  401229:	41 54                	push   %r12
  40122b:	55                   	push   %rbp
  40122c:	53                   	push   %rbx
  40122d:	48 83 ec 68          	sub    $0x68,%rsp
  401231:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401238:	00 00 
  40123a:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
  40123f:	31 c0                	xor    %eax,%eax
  401241:	48 89 e6             	mov    %rsp,%rsi
  401244:	e8 c0 05 00 00       	callq  401809 <read_six_numbers>
  401249:	49 89 e4             	mov    %rsp,%r12
  40124c:	41 bd 00 00 00 00    	mov    $0x0,%r13d
  401252:	4c 89 e5             	mov    %r12,%rbp
  401255:	41 8b 04 24          	mov    (%r12),%eax
  401259:	83 e8 01             	sub    $0x1,%eax
  40125c:	83 f8 05             	cmp    $0x5,%eax
  40125f:	76 05                	jbe    401266 <phase_6+0x3f>
  401261:	e8 6d 05 00 00       	callq  4017d3 <explode_bomb>
  401266:	41 83 c5 01          	add    $0x1,%r13d
  40126a:	41 83 fd 06          	cmp    $0x6,%r13d
  40126e:	74 3d                	je     4012ad <phase_6+0x86>
  401270:	44 89 eb             	mov    %r13d,%ebx
  401273:	48 63 c3             	movslq %ebx,%rax
  401276:	8b 04 84             	mov    (%rsp,%rax,4),%eax
  401279:	39 45 00             	cmp    %eax,0x0(%rbp)
  40127c:	75 05                	jne    401283 <phase_6+0x5c>
  40127e:	e8 50 05 00 00       	callq  4017d3 <explode_bomb>
  401283:	83 c3 01             	add    $0x1,%ebx
  401286:	83 fb 05             	cmp    $0x5,%ebx
  401289:	7e e8                	jle    401273 <phase_6+0x4c>
  40128b:	49 83 c4 04          	add    $0x4,%r12
  40128f:	eb c1                	jmp    401252 <phase_6+0x2b>
  401291:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  401295:	83 c0 01             	add    $0x1,%eax
  401298:	39 c8                	cmp    %ecx,%eax
  40129a:	75 f5                	jne    401291 <phase_6+0x6a>
  40129c:	48 89 54 74 20       	mov    %rdx,0x20(%rsp,%rsi,2)
  4012a1:	48 83 c6 04          	add    $0x4,%rsi
  4012a5:	48 83 fe 18          	cmp    $0x18,%rsi (stacke 6 tane sayı 0x6042f0 eklemesinin sonu)
  4012a9:	75 07                	jne    4012b2 <phase_6+0x8b>
  4012ab:	eb 19                	jmp    4012c6 <phase_6+0x9f>
  4012ad:	be 00 00 00 00       	mov    $0x0,%esi (5ten küçük mü ve farklı sayılar mı kontrol sonu)
  4012b2:	8b 0c 34             	mov    (%rsp,%rsi,1),%ecx
  4012b5:	b8 01 00 00 00       	mov    $0x1,%eax
  4012ba:	ba f0 42 60 00       	mov    $0x6042f0,%edx
  4012bf:	83 f9 01             	cmp    $0x1,%ecx
  4012c2:	7f cd                	jg     401291 <phase_6+0x6a>
  4012c4:	eb d6                	jmp    40129c <phase_6+0x75>
  4012c6:	48 8b 5c 24 20       	mov    0x20(%rsp),%rbx (stacke yerleştirdiğin burdan başlıyor) (yerleştirdiğin ilk sayı rsp+20de diğeri rsp+28de gidiyo böyle)
  4012cb:	48 8d 44 24 20       	lea    0x20(%rsp),%rax (ilk değerin adresi)
  4012d0:	48 8d 74 24 48       	lea    0x48(%rsp),%rsi  (en son değerin adresi)
  4012d5:	48 89 d9             	mov    %rbx,%rcx (rcxte ilk sayı var)
  4012d8:	48 8b 50 08          	mov    0x8(%rax),%rdx  (rdxde ikinci sayı var artık) (rdxte 3. sayı var)
  4012dc:	48 89 51 08          	mov    %rdx,0x8(%rcx) (ikinci sayı ikincinin point ettiği yere yazılıyor) (3. sayı ikinci sayının +8ine yazılıyor)
  4012e0:	48 83 c0 08          	add    $0x8,%rax (raxde artık ikinci sayının adresi var)
  4012e4:	48 89 d1             	mov    %rdx,%rcx (rcxte ikinci sayı var artık)
  4012e7:	48 39 f0             	cmp    %rsi,%rax (loop)
  4012ea:	75 ec                	jne    4012d8 <phase_6+0xb1>
  4012ec:	48 c7 42 08 00 00 00 	movq   $0x0,0x8(%rdx)
  4012f3:	00 
  4012f4:	bd 00 00 00 00       	mov    $0x0,%ebp
  4012f9:	40 f6 c5 01          	test   $0x1,%bpl
  4012fd:	75 11                	jne    401310 <phase_6+0xe9>
  4012ff:	48 8b 43 08          	mov    0x8(%rbx),%rax
  401303:	8b 00                	mov    (%rax),%eax
  401305:	39 03                	cmp    %eax,(%rbx)
  401307:	7d 16                	jge    40131f <phase_6+0xf8>
  401309:	e8 c5 04 00 00       	callq  4017d3 <explode_bomb>
  40130e:	eb 0f                	jmp    40131f <phase_6+0xf8>
  401310:	48 8b 43 08          	mov    0x8(%rbx),%rax
  401314:	8b 00                	mov    (%rax),%eax
  401316:	39 03                	cmp    %eax,(%rbx)
  401318:	7e 05                	jle    40131f <phase_6+0xf8>
  40131a:	e8 b4 04 00 00       	callq  4017d3 <explode_bomb>
  40131f:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
  401323:	83 c5 01             	add    $0x1,%ebp
  401326:	83 fd 05             	cmp    $0x5,%ebp
  401329:	75 ce                	jne    4012f9 <phase_6+0xd2>
  40132b:	48 8b 44 24 58       	mov    0x58(%rsp),%rax
  401330:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401337:	00 00 
  401339:	74 05                	je     401340 <phase_6+0x119>
  40133b:	e8 a0 f8 ff ff       	callq  400be0 <__stack_chk_fail@plt>
  401340:	48 83 c4 68          	add    $0x68,%rsp
  401344:	5b                   	pop    %rbx
  401345:	5d                   	pop    %rbp
  401346:	41 5c                	pop    %r12
  401348:	41 5d                	pop    %r13
  40134a:	c3                   	retq   

000000000040134b <fun7>:
  40134b:	48 83 ec 08          	sub    $0x8,%rsp
  40134f:	48 85 ff             	test   %rdi,%rdi
  401352:	74 2b                	je     40137f <fun7+0x34>
  401354:	8b 17                	mov    (%rdi),%edx
  401356:	39 f2                	cmp    %esi,%edx
  401358:	7e 0d                	jle    401367 <fun7+0x1c>
  40135a:	48 8b 7f 08          	mov    0x8(%rdi),%rdi
  40135e:	e8 e8 ff ff ff       	callq  40134b <fun7>
  401363:	01 c0                	add    %eax,%eax
  401365:	eb 1d                	jmp    401384 <fun7+0x39>
  401367:	b8 00 00 00 00       	mov    $0x0,%eax
  40136c:	39 f2                	cmp    %esi,%edx
  40136e:	74 14                	je     401384 <fun7+0x39>
  401370:	48 8b 7f 10          	mov    0x10(%rdi),%rdi
  401374:	e8 d2 ff ff ff       	callq  40134b <fun7>
  401379:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  40137d:	eb 05                	jmp    401384 <fun7+0x39>
  40137f:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401384:	48 83 c4 08          	add    $0x8,%rsp
  401388:	c3                   	retq   

0000000000401389 <secret_phase>:
  401389:	53                   	push   %rbx
  40138a:	e8 b9 04 00 00       	callq  401848 <read_line>
  40138f:	ba 0a 00 00 00       	mov    $0xa,%edx
  401394:	be 00 00 00 00       	mov    $0x0,%esi
  401399:	48 89 c7             	mov    %rax,%rdi
  40139c:	e8 cf f8 ff ff       	callq  400c70 <strtol@plt>
  4013a1:	48 89 c3             	mov    %rax,%rbx
  4013a4:	8d 40 ff             	lea    -0x1(%rax),%eax
  4013a7:	3d e8 03 00 00       	cmp    $0x3e8,%eax
  4013ac:	76 05                	jbe    4013b3 <secret_phase+0x2a>
  4013ae:	e8 20 04 00 00       	callq  4017d3 <explode_bomb>
  4013b3:	89 de                	mov    %ebx,%esi
  4013b5:	bf 10 41 60 00       	mov    $0x604110,%edi
  4013ba:	e8 8c ff ff ff       	callq  40134b <fun7>
  4013bf:	83 f8 07             	cmp    $0x7,%eax
  4013c2:	74 05                	je     4013c9 <secret_phase+0x40>
  4013c4:	e8 0a 04 00 00       	callq  4017d3 <explode_bomb>
  4013c9:	bf b8 27 40 00       	mov    $0x4027b8,%edi
  4013ce:	e8 ed f7 ff ff       	callq  400bc0 <puts@plt>
  4013d3:	e8 96 05 00 00       	callq  40196e <phase_defused>
  4013d8:	5b                   	pop    %rbx
  4013d9:	c3                   	retq   

00000000004013da <sig_handler>:
  4013da:	48 83 ec 08          	sub    $0x8,%rsp
  4013de:	bf 60 28 40 00       	mov    $0x402860,%edi
  4013e3:	e8 d8 f7 ff ff       	callq  400bc0 <puts@plt>
  4013e8:	bf 03 00 00 00       	mov    $0x3,%edi
  4013ed:	e8 0e f9 ff ff       	callq  400d00 <sleep@plt>
  4013f2:	be 29 2a 40 00       	mov    $0x402a29,%esi
  4013f7:	bf 01 00 00 00       	mov    $0x1,%edi
  4013fc:	b8 00 00 00 00       	mov    $0x0,%eax
  401401:	e8 9a f8 ff ff       	callq  400ca0 <__printf_chk@plt>
  401406:	48 8b 3d 73 33 20 00 	mov    0x203373(%rip),%rdi        # 604780 <stdout@@GLIBC_2.2.5>
  40140d:	e8 6e f8 ff ff       	callq  400c80 <fflush@plt>
  401412:	bf 01 00 00 00       	mov    $0x1,%edi
  401417:	e8 e4 f8 ff ff       	callq  400d00 <sleep@plt>
  40141c:	bf 31 2a 40 00       	mov    $0x402a31,%edi
  401421:	e8 9a f7 ff ff       	callq  400bc0 <puts@plt>
  401426:	bf 10 00 00 00       	mov    $0x10,%edi
  40142b:	e8 a0 f8 ff ff       	callq  400cd0 <exit@plt>

0000000000401430 <invalid_phase>:
  401430:	48 83 ec 08          	sub    $0x8,%rsp
  401434:	48 89 fa             	mov    %rdi,%rdx
  401437:	be 39 2a 40 00       	mov    $0x402a39,%esi
  40143c:	bf 01 00 00 00       	mov    $0x1,%edi
  401441:	b8 00 00 00 00       	mov    $0x0,%eax
  401446:	e8 55 f8 ff ff       	callq  400ca0 <__printf_chk@plt>
  40144b:	bf 08 00 00 00       	mov    $0x8,%edi
  401450:	e8 7b f8 ff ff       	callq  400cd0 <exit@plt>

0000000000401455 <string_length>:
  401455:	80 3f 00             	cmpb   $0x0,(%rdi)
  401458:	74 13                	je     40146d <string_length+0x18>
  40145a:	b8 00 00 00 00       	mov    $0x0,%eax
  40145f:	48 83 c7 01          	add    $0x1,%rdi
  401463:	83 c0 01             	add    $0x1,%eax
  401466:	80 3f 00             	cmpb   $0x0,(%rdi)
  401469:	75 f4                	jne    40145f <string_length+0xa>
  40146b:	f3 c3                	repz retq 
  40146d:	b8 00 00 00 00       	mov    $0x0,%eax
  401472:	c3                   	retq   

0000000000401473 <check_division_equal>:
  401473:	89 d1                	mov    %edx,%ecx
  401475:	89 f8                	mov    %edi,%eax
  401477:	99                   	cltd   
  401478:	f7 fe                	idiv   %esi
  40147a:	39 c8                	cmp    %ecx,%eax
  40147c:	0f 94 c0             	sete   %al
  40147f:	0f b6 c0             	movzbl %al,%eax
  401482:	c3                   	retq   

0000000000401483 <check_multiplication_equal>:
  401483:	0f af f7             	imul   %edi,%esi
  401486:	39 d6                	cmp    %edx,%esi
  401488:	0f 94 c0             	sete   %al
  40148b:	0f b6 c0             	movzbl %al,%eax
  40148e:	c3                   	retq   

000000000040148f <check_substraction_equal>:
  40148f:	29 f7                	sub    %esi,%edi
  401491:	39 d7                	cmp    %edx,%edi
  401493:	0f 94 c0             	sete   %al
  401496:	0f b6 c0             	movzbl %al,%eax
  401499:	c3                   	retq   

000000000040149a <reverse_string>:
  40149a:	48 89 fe             	mov    %rdi,%rsi
  40149d:	48 85 ff             	test   %rdi,%rdi
  4014a0:	74 3d                	je     4014df <reverse_string+0x45>
  4014a2:	80 3f 00             	cmpb   $0x0,(%rdi)
  4014a5:	74 38                	je     4014df <reverse_string+0x45>
  4014a7:	b8 00 00 00 00       	mov    $0x0,%eax
  4014ac:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4014b3:	f2 ae                	repnz scas %es:(%rdi),%al
  4014b5:	48 f7 d1             	not    %rcx
  4014b8:	48 8d 4c 0e fe       	lea    -0x2(%rsi,%rcx,1),%rcx
  4014bd:	48 39 ce             	cmp    %rcx,%rsi
  4014c0:	73 1d                	jae    4014df <reverse_string+0x45>
  4014c2:	48 89 f2             	mov    %rsi,%rdx
  4014c5:	0f b6 02             	movzbl (%rdx),%eax
  4014c8:	32 01                	xor    (%rcx),%al
  4014ca:	88 02                	mov    %al,(%rdx)
  4014cc:	32 01                	xor    (%rcx),%al
  4014ce:	88 01                	mov    %al,(%rcx)
  4014d0:	30 02                	xor    %al,(%rdx)
  4014d2:	48 83 c2 01          	add    $0x1,%rdx
  4014d6:	48 83 e9 01          	sub    $0x1,%rcx
  4014da:	48 39 ca             	cmp    %rcx,%rdx
  4014dd:	72 e6                	jb     4014c5 <reverse_string+0x2b>
  4014df:	48 89 f0             	mov    %rsi,%rax
  4014e2:	c3                   	retq   

00000000004014e3 <strings_not_equal>:
  4014e3:	41 54                	push   %r12
  4014e5:	55                   	push   %rbp
  4014e6:	53                   	push   %rbx
  4014e7:	48 89 fb             	mov    %rdi,%rbx
  4014ea:	48 89 f5             	mov    %rsi,%rbp
  4014ed:	e8 63 ff ff ff       	callq  401455 <string_length>
  4014f2:	41 89 c4             	mov    %eax,%r12d
  4014f5:	48 89 ef             	mov    %rbp,%rdi
  4014f8:	e8 58 ff ff ff       	callq  401455 <string_length>
  4014fd:	ba 01 00 00 00       	mov    $0x1,%edx
  401502:	41 39 c4             	cmp    %eax,%r12d
  401505:	75 3c                	jne    401543 <strings_not_equal+0x60>
  401507:	0f b6 03             	movzbl (%rbx),%eax
  40150a:	84 c0                	test   %al,%al
  40150c:	74 22                	je     401530 <strings_not_equal+0x4d>
  40150e:	3a 45 00             	cmp    0x0(%rbp),%al
  401511:	74 07                	je     40151a <strings_not_equal+0x37>
  401513:	eb 22                	jmp    401537 <strings_not_equal+0x54>
  401515:	3a 45 00             	cmp    0x0(%rbp),%al
  401518:	75 24                	jne    40153e <strings_not_equal+0x5b>
  40151a:	48 83 c3 01          	add    $0x1,%rbx
  40151e:	48 83 c5 01          	add    $0x1,%rbp
  401522:	0f b6 03             	movzbl (%rbx),%eax
  401525:	84 c0                	test   %al,%al
  401527:	75 ec                	jne    401515 <strings_not_equal+0x32>
  401529:	ba 00 00 00 00       	mov    $0x0,%edx
  40152e:	eb 13                	jmp    401543 <strings_not_equal+0x60>
  401530:	ba 00 00 00 00       	mov    $0x0,%edx
  401535:	eb 0c                	jmp    401543 <strings_not_equal+0x60>
  401537:	ba 01 00 00 00       	mov    $0x1,%edx
  40153c:	eb 05                	jmp    401543 <strings_not_equal+0x60>
  40153e:	ba 01 00 00 00       	mov    $0x1,%edx
  401543:	89 d0                	mov    %edx,%eax
  401545:	5b                   	pop    %rbx
  401546:	5d                   	pop    %rbp
  401547:	41 5c                	pop    %r12
  401549:	c3                   	retq   

000000000040154a <from_char_to_int>:
  40154a:	40 0f be c7          	movsbl %dil,%eax
  40154e:	40 80 ff 69          	cmp    $0x69,%dil
  401552:	7e 04                	jle    401558 <from_char_to_int+0xe>
  401554:	83 e8 09             	sub    $0x9,%eax
  401557:	c3                   	retq   
  401558:	83 ef 33             	sub    $0x33,%edi
  40155b:	8d 50 fd             	lea    -0x3(%rax),%edx
  40155e:	40 80 ff 09          	cmp    $0x9,%dil
  401562:	0f 46 c2             	cmovbe %edx,%eax
  401565:	c3                   	retq   

0000000000401566 <initialize_bomb>:
  401566:	53                   	push   %rbx
  401567:	48 81 ec 50 20 00 00 	sub    $0x2050,%rsp
  40156e:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401575:	00 00 
  401577:	48 89 84 24 48 20 00 	mov    %rax,0x2048(%rsp)
  40157e:	00 
  40157f:	31 c0                	xor    %eax,%eax
  401581:	be da 13 40 00       	mov    $0x4013da,%esi
  401586:	bf 02 00 00 00       	mov    $0x2,%edi
  40158b:	e8 b0 f6 ff ff       	callq  400c40 <signal@plt>
  401590:	be 40 00 00 00       	mov    $0x40,%esi
  401595:	48 89 e7             	mov    %rsp,%rdi
  401598:	e8 23 f7 ff ff       	callq  400cc0 <gethostname@plt>
  40159d:	85 c0                	test   %eax,%eax
  40159f:	75 13                	jne    4015b4 <initialize_bomb+0x4e>
  4015a1:	48 8b 3d d8 2d 20 00 	mov    0x202dd8(%rip),%rdi        # 604380 <host_table>
  4015a8:	bb 88 43 60 00       	mov    $0x604388,%ebx
  4015ad:	48 85 ff             	test   %rdi,%rdi
  4015b0:	75 16                	jne    4015c8 <initialize_bomb+0x62>
  4015b2:	eb 52                	jmp    401606 <initialize_bomb+0xa0>
  4015b4:	bf 98 28 40 00       	mov    $0x402898,%edi
  4015b9:	e8 02 f6 ff ff       	callq  400bc0 <puts@plt>
  4015be:	bf 08 00 00 00       	mov    $0x8,%edi
  4015c3:	e8 08 f7 ff ff       	callq  400cd0 <exit@plt>
  4015c8:	48 89 e6             	mov    %rsp,%rsi
  4015cb:	e8 c0 f5 ff ff       	callq  400b90 <strcasecmp@plt>
  4015d0:	85 c0                	test   %eax,%eax
  4015d2:	74 46                	je     40161a <initialize_bomb+0xb4>
  4015d4:	48 83 c3 08          	add    $0x8,%rbx
  4015d8:	48 8b 7b f8          	mov    -0x8(%rbx),%rdi
  4015dc:	48 85 ff             	test   %rdi,%rdi
  4015df:	75 e7                	jne    4015c8 <initialize_bomb+0x62>
  4015e1:	eb 23                	jmp    401606 <initialize_bomb+0xa0>
  4015e3:	48 8d 54 24 40       	lea    0x40(%rsp),%rdx
  4015e8:	be 4a 2a 40 00       	mov    $0x402a4a,%esi
  4015ed:	bf 01 00 00 00       	mov    $0x1,%edi
  4015f2:	b8 00 00 00 00       	mov    $0x0,%eax
  4015f7:	e8 a4 f6 ff ff       	callq  400ca0 <__printf_chk@plt>
  4015fc:	bf 08 00 00 00       	mov    $0x8,%edi
  401601:	e8 ca f6 ff ff       	callq  400cd0 <exit@plt>
  401606:	bf d0 28 40 00       	mov    $0x4028d0,%edi
  40160b:	e8 b0 f5 ff ff       	callq  400bc0 <puts@plt>
  401610:	bf 08 00 00 00       	mov    $0x8,%edi
  401615:	e8 b6 f6 ff ff       	callq  400cd0 <exit@plt>
  40161a:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  40161f:	e8 49 0d 00 00       	callq  40236d <init_driver>
  401624:	85 c0                	test   %eax,%eax
  401626:	78 bb                	js     4015e3 <initialize_bomb+0x7d>
  401628:	48 8b 84 24 48 20 00 	mov    0x2048(%rsp),%rax
  40162f:	00 
  401630:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401637:	00 00 
  401639:	74 05                	je     401640 <initialize_bomb+0xda>
  40163b:	e8 a0 f5 ff ff       	callq  400be0 <__stack_chk_fail@plt>
  401640:	48 81 c4 50 20 00 00 	add    $0x2050,%rsp
  401647:	5b                   	pop    %rbx
  401648:	c3                   	retq   

0000000000401649 <initialize_bomb_solve>:
  401649:	f3 c3                	repz retq 

000000000040164b <blank_line>:
  40164b:	55                   	push   %rbp
  40164c:	53                   	push   %rbx
  40164d:	48 83 ec 08          	sub    $0x8,%rsp
  401651:	48 89 fd             	mov    %rdi,%rbp
  401654:	eb 17                	jmp    40166d <blank_line+0x22>
  401656:	e8 b5 f6 ff ff       	callq  400d10 <__ctype_b_loc@plt>
  40165b:	48 83 c5 01          	add    $0x1,%rbp
  40165f:	48 0f be db          	movsbq %bl,%rbx
  401663:	48 8b 00             	mov    (%rax),%rax
  401666:	f6 44 58 01 20       	testb  $0x20,0x1(%rax,%rbx,2)
  40166b:	74 0f                	je     40167c <blank_line+0x31>
  40166d:	0f b6 5d 00          	movzbl 0x0(%rbp),%ebx
  401671:	84 db                	test   %bl,%bl
  401673:	75 e1                	jne    401656 <blank_line+0xb>
  401675:	b8 01 00 00 00       	mov    $0x1,%eax
  40167a:	eb 05                	jmp    401681 <blank_line+0x36>
  40167c:	b8 00 00 00 00       	mov    $0x0,%eax
  401681:	48 83 c4 08          	add    $0x8,%rsp
  401685:	5b                   	pop    %rbx
  401686:	5d                   	pop    %rbp
  401687:	c3                   	retq   

0000000000401688 <skip>:
  401688:	53                   	push   %rbx
  401689:	48 63 05 1c 31 20 00 	movslq 0x20311c(%rip),%rax        # 6047ac <num_input_strings>
  401690:	48 8d 3c 80          	lea    (%rax,%rax,4),%rdi
  401694:	48 c1 e7 04          	shl    $0x4,%rdi
  401698:	48 81 c7 c0 47 60 00 	add    $0x6047c0,%rdi
  40169f:	48 8b 15 0a 31 20 00 	mov    0x20310a(%rip),%rdx        # 6047b0 <infile>
  4016a6:	be 50 00 00 00       	mov    $0x50,%esi
  4016ab:	e8 80 f5 ff ff       	callq  400c30 <fgets@plt>
  4016b0:	48 89 c3             	mov    %rax,%rbx
  4016b3:	48 85 c0             	test   %rax,%rax
  4016b6:	74 0c                	je     4016c4 <skip+0x3c>
  4016b8:	48 89 c7             	mov    %rax,%rdi
  4016bb:	e8 8b ff ff ff       	callq  40164b <blank_line>
  4016c0:	85 c0                	test   %eax,%eax
  4016c2:	75 c5                	jne    401689 <skip+0x1>
  4016c4:	48 89 d8             	mov    %rbx,%rax
  4016c7:	5b                   	pop    %rbx
  4016c8:	c3                   	retq   

00000000004016c9 <send_msg>:
  4016c9:	48 81 ec 18 40 00 00 	sub    $0x4018,%rsp
  4016d0:	41 89 f8             	mov    %edi,%r8d
  4016d3:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4016da:	00 00 
  4016dc:	48 89 84 24 08 40 00 	mov    %rax,0x4008(%rsp)
  4016e3:	00 
  4016e4:	31 c0                	xor    %eax,%eax
  4016e6:	8b 35 c0 30 20 00    	mov    0x2030c0(%rip),%esi        # 6047ac <num_input_strings>
  4016ec:	8d 46 ff             	lea    -0x1(%rsi),%eax
  4016ef:	48 98                	cltq   
  4016f1:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
  4016f5:	48 c1 e2 04          	shl    $0x4,%rdx
  4016f9:	48 81 c2 c0 47 60 00 	add    $0x6047c0,%rdx
  401700:	b8 00 00 00 00       	mov    $0x0,%eax
  401705:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40170c:	48 89 d7             	mov    %rdx,%rdi
  40170f:	f2 ae                	repnz scas %es:(%rdi),%al
  401711:	48 f7 d1             	not    %rcx
  401714:	48 83 c1 63          	add    $0x63,%rcx
  401718:	48 81 f9 00 20 00 00 	cmp    $0x2000,%rcx
  40171f:	76 19                	jbe    40173a <send_msg+0x71>
  401721:	be 08 29 40 00       	mov    $0x402908,%esi
  401726:	bf 01 00 00 00       	mov    $0x1,%edi
  40172b:	e8 70 f5 ff ff       	callq  400ca0 <__printf_chk@plt>
  401730:	bf 08 00 00 00       	mov    $0x8,%edi
  401735:	e8 96 f5 ff ff       	callq  400cd0 <exit@plt>
  40173a:	45 85 c0             	test   %r8d,%r8d
  40173d:	41 b9 6c 2a 40 00    	mov    $0x402a6c,%r9d
  401743:	b8 64 2a 40 00       	mov    $0x402a64,%eax
  401748:	4c 0f 45 c8          	cmovne %rax,%r9
  40174c:	52                   	push   %rdx
  40174d:	56                   	push   %rsi
  40174e:	44 8b 05 1b 2c 20 00 	mov    0x202c1b(%rip),%r8d        # 604370 <bomb_id>
  401755:	b9 75 2a 40 00       	mov    $0x402a75,%ecx
  40175a:	ba 00 20 00 00       	mov    $0x2000,%edx
  40175f:	be 01 00 00 00       	mov    $0x1,%esi
  401764:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  401769:	b8 00 00 00 00       	mov    $0x0,%eax
  40176e:	e8 ad f5 ff ff       	callq  400d20 <__sprintf_chk@plt>
  401773:	4c 8d 84 24 10 20 00 	lea    0x2010(%rsp),%r8
  40177a:	00 
  40177b:	b9 00 00 00 00       	mov    $0x0,%ecx
  401780:	48 8d 54 24 10       	lea    0x10(%rsp),%rdx
  401785:	be 50 43 60 00       	mov    $0x604350,%esi
  40178a:	bf 68 43 60 00       	mov    $0x604368,%edi
  40178f:	e8 ae 0d 00 00       	callq  402542 <driver_post>
  401794:	48 83 c4 10          	add    $0x10,%rsp
  401798:	85 c0                	test   %eax,%eax
  40179a:	79 17                	jns    4017b3 <send_msg+0xea>
  40179c:	48 8d bc 24 00 20 00 	lea    0x2000(%rsp),%rdi
  4017a3:	00 
  4017a4:	e8 17 f4 ff ff       	callq  400bc0 <puts@plt>
  4017a9:	bf 00 00 00 00       	mov    $0x0,%edi
  4017ae:	e8 1d f5 ff ff       	callq  400cd0 <exit@plt>
  4017b3:	48 8b 84 24 08 40 00 	mov    0x4008(%rsp),%rax
  4017ba:	00 
  4017bb:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4017c2:	00 00 
  4017c4:	74 05                	je     4017cb <send_msg+0x102>
  4017c6:	e8 15 f4 ff ff       	callq  400be0 <__stack_chk_fail@plt>
  4017cb:	48 81 c4 18 40 00 00 	add    $0x4018,%rsp
  4017d2:	c3                   	retq   

00000000004017d3 <explode_bomb>:
  4017d3:	48 83 ec 08          	sub    $0x8,%rsp
  4017d7:	bf 81 2a 40 00       	mov    $0x402a81,%edi
  4017dc:	e8 df f3 ff ff       	callq  400bc0 <puts@plt>
  4017e1:	bf 8a 2a 40 00       	mov    $0x402a8a,%edi
  4017e6:	e8 d5 f3 ff ff       	callq  400bc0 <puts@plt>
  4017eb:	bf 00 00 00 00       	mov    $0x0,%edi
  4017f0:	e8 d4 fe ff ff       	callq  4016c9 <send_msg>
  4017f5:	bf 30 29 40 00       	mov    $0x402930,%edi
  4017fa:	e8 c1 f3 ff ff       	callq  400bc0 <puts@plt>
  4017ff:	bf 08 00 00 00       	mov    $0x8,%edi
  401804:	e8 c7 f4 ff ff       	callq  400cd0 <exit@plt>

0000000000401809 <read_six_numbers>:
  401809:	48 83 ec 08          	sub    $0x8,%rsp
  40180d:	48 89 f2             	mov    %rsi,%rdx
  401810:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
  401814:	48 8d 46 14          	lea    0x14(%rsi),%rax
  401818:	50                   	push   %rax
  401819:	48 8d 46 10          	lea    0x10(%rsi),%rax
  40181d:	50                   	push   %rax
  40181e:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
  401822:	4c 8d 46 08          	lea    0x8(%rsi),%r8
  401826:	be a1 2a 40 00       	mov    $0x402aa1,%esi
  40182b:	b8 00 00 00 00       	mov    $0x0,%eax
  401830:	e8 5b f4 ff ff       	callq  400c90 <__isoc99_sscanf@plt>
  401835:	48 83 c4 10          	add    $0x10,%rsp
  401839:	83 f8 05             	cmp    $0x5,%eax
  40183c:	7f 05                	jg     401843 <read_six_numbers+0x3a>
  40183e:	e8 90 ff ff ff       	callq  4017d3 <explode_bomb>
  401843:	48 83 c4 08          	add    $0x8,%rsp
  401847:	c3                   	retq   

0000000000401848 <read_line>:
  401848:	48 83 ec 08          	sub    $0x8,%rsp
  40184c:	b8 00 00 00 00       	mov    $0x0,%eax
  401851:	e8 32 fe ff ff       	callq  401688 <skip>
  401856:	48 85 c0             	test   %rax,%rax
  401859:	75 6e                	jne    4018c9 <read_line+0x81>
  40185b:	48 8b 05 2e 2f 20 00 	mov    0x202f2e(%rip),%rax        # 604790 <stdin@@GLIBC_2.2.5>
  401862:	48 39 05 47 2f 20 00 	cmp    %rax,0x202f47(%rip)        # 6047b0 <infile>
  401869:	75 14                	jne    40187f <read_line+0x37>
  40186b:	bf b3 2a 40 00       	mov    $0x402ab3,%edi
  401870:	e8 4b f3 ff ff       	callq  400bc0 <puts@plt>
  401875:	bf 08 00 00 00       	mov    $0x8,%edi
  40187a:	e8 51 f4 ff ff       	callq  400cd0 <exit@plt>
  40187f:	bf d1 2a 40 00       	mov    $0x402ad1,%edi
  401884:	e8 f7 f2 ff ff       	callq  400b80 <getenv@plt>
  401889:	48 85 c0             	test   %rax,%rax
  40188c:	74 0a                	je     401898 <read_line+0x50>
  40188e:	bf 00 00 00 00       	mov    $0x0,%edi
  401893:	e8 38 f4 ff ff       	callq  400cd0 <exit@plt>
  401898:	48 8b 05 f1 2e 20 00 	mov    0x202ef1(%rip),%rax        # 604790 <stdin@@GLIBC_2.2.5>
  40189f:	48 89 05 0a 2f 20 00 	mov    %rax,0x202f0a(%rip)        # 6047b0 <infile>
  4018a6:	b8 00 00 00 00       	mov    $0x0,%eax
  4018ab:	e8 d8 fd ff ff       	callq  401688 <skip>
  4018b0:	48 85 c0             	test   %rax,%rax
  4018b3:	75 14                	jne    4018c9 <read_line+0x81>
  4018b5:	bf b3 2a 40 00       	mov    $0x402ab3,%edi
  4018ba:	e8 01 f3 ff ff       	callq  400bc0 <puts@plt>
  4018bf:	bf 00 00 00 00       	mov    $0x0,%edi
  4018c4:	e8 07 f4 ff ff       	callq  400cd0 <exit@plt>
  4018c9:	8b 35 dd 2e 20 00    	mov    0x202edd(%rip),%esi        # 6047ac <num_input_strings>
  4018cf:	48 63 c6             	movslq %esi,%rax
  4018d2:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
  4018d6:	48 c1 e2 04          	shl    $0x4,%rdx
  4018da:	48 81 c2 c0 47 60 00 	add    $0x6047c0,%rdx
  4018e1:	b8 00 00 00 00       	mov    $0x0,%eax
  4018e6:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4018ed:	48 89 d7             	mov    %rdx,%rdi
  4018f0:	f2 ae                	repnz scas %es:(%rdi),%al
  4018f2:	48 f7 d1             	not    %rcx
  4018f5:	48 83 e9 01          	sub    $0x1,%rcx
  4018f9:	83 f9 4e             	cmp    $0x4e,%ecx
  4018fc:	7e 46                	jle    401944 <read_line+0xfc>
  4018fe:	bf dc 2a 40 00       	mov    $0x402adc,%edi
  401903:	e8 b8 f2 ff ff       	callq  400bc0 <puts@plt>
  401908:	8b 05 9e 2e 20 00    	mov    0x202e9e(%rip),%eax        # 6047ac <num_input_strings>
  40190e:	8d 50 01             	lea    0x1(%rax),%edx
  401911:	89 15 95 2e 20 00    	mov    %edx,0x202e95(%rip)        # 6047ac <num_input_strings>
  401917:	48 98                	cltq   
  401919:	48 6b c0 50          	imul   $0x50,%rax,%rax
  40191d:	48 bf 2a 2a 2a 74 72 	movabs $0x636e7572742a2a2a,%rdi
  401924:	75 6e 63 
  401927:	48 89 b8 c0 47 60 00 	mov    %rdi,0x6047c0(%rax)
  40192e:	48 bf 61 74 65 64 2a 	movabs $0x2a2a2a64657461,%rdi
  401935:	2a 2a 00 
  401938:	48 89 b8 c8 47 60 00 	mov    %rdi,0x6047c8(%rax)
  40193f:	e8 8f fe ff ff       	callq  4017d3 <explode_bomb>
  401944:	83 e9 01             	sub    $0x1,%ecx
  401947:	48 63 c9             	movslq %ecx,%rcx
  40194a:	48 63 c6             	movslq %esi,%rax
  40194d:	48 8d 04 80          	lea    (%rax,%rax,4),%rax
  401951:	48 c1 e0 04          	shl    $0x4,%rax
  401955:	c6 84 01 c0 47 60 00 	movb   $0x0,0x6047c0(%rcx,%rax,1)
  40195c:	00 
  40195d:	8d 46 01             	lea    0x1(%rsi),%eax
  401960:	89 05 46 2e 20 00    	mov    %eax,0x202e46(%rip)        # 6047ac <num_input_strings>
  401966:	48 89 d0             	mov    %rdx,%rax
  401969:	48 83 c4 08          	add    $0x8,%rsp
  40196d:	c3                   	retq   

000000000040196e <phase_defused>:
  40196e:	48 83 ec 78          	sub    $0x78,%rsp
  401972:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401979:	00 00 
  40197b:	48 89 44 24 68       	mov    %rax,0x68(%rsp)
  401980:	31 c0                	xor    %eax,%eax
  401982:	bf 01 00 00 00       	mov    $0x1,%edi
  401987:	e8 3d fd ff ff       	callq  4016c9 <send_msg>
  40198c:	83 3d 19 2e 20 00 06 	cmpl   $0x6,0x202e19(%rip)        # 6047ac <num_input_strings>
  401993:	75 6d                	jne    401a02 <phase_defused+0x94>
  401995:	4c 8d 44 24 10       	lea    0x10(%rsp),%r8
  40199a:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  40199f:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  4019a4:	be f7 2a 40 00       	mov    $0x402af7,%esi
  4019a9:	bf b0 48 60 00       	mov    $0x6048b0,%edi
  4019ae:	b8 00 00 00 00       	mov    $0x0,%eax
  4019b3:	e8 d8 f2 ff ff       	callq  400c90 <__isoc99_sscanf@plt>
  4019b8:	83 f8 03             	cmp    $0x3,%eax
  4019bb:	75 31                	jne    4019ee <phase_defused+0x80>
  4019bd:	be 00 2b 40 00       	mov    $0x402b00,%esi
  4019c2:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  4019c7:	e8 17 fb ff ff       	callq  4014e3 <strings_not_equal>
  4019cc:	85 c0                	test   %eax,%eax
  4019ce:	75 1e                	jne    4019ee <phase_defused+0x80>
  4019d0:	bf 58 29 40 00       	mov    $0x402958,%edi
  4019d5:	e8 e6 f1 ff ff       	callq  400bc0 <puts@plt>
  4019da:	bf 80 29 40 00       	mov    $0x402980,%edi
  4019df:	e8 dc f1 ff ff       	callq  400bc0 <puts@plt>
  4019e4:	b8 00 00 00 00       	mov    $0x0,%eax
  4019e9:	e8 9b f9 ff ff       	callq  401389 <secret_phase>
  4019ee:	bf b8 29 40 00       	mov    $0x4029b8,%edi
  4019f3:	e8 c8 f1 ff ff       	callq  400bc0 <puts@plt>
  4019f8:	bf e8 29 40 00       	mov    $0x4029e8,%edi
  4019fd:	e8 be f1 ff ff       	callq  400bc0 <puts@plt>
  401a02:	48 8b 44 24 68       	mov    0x68(%rsp),%rax
  401a07:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401a0e:	00 00 
  401a10:	74 05                	je     401a17 <phase_defused+0xa9>
  401a12:	e8 c9 f1 ff ff       	callq  400be0 <__stack_chk_fail@plt>
  401a17:	48 83 c4 78          	add    $0x78,%rsp
  401a1b:	c3                   	retq   

0000000000401a1c <sigalrm_handler>:
  401a1c:	48 83 ec 08          	sub    $0x8,%rsp
  401a20:	b9 00 00 00 00       	mov    $0x0,%ecx
  401a25:	ba d8 2d 40 00       	mov    $0x402dd8,%edx
  401a2a:	be 01 00 00 00       	mov    $0x1,%esi
  401a2f:	48 8b 3d 6a 2d 20 00 	mov    0x202d6a(%rip),%rdi        # 6047a0 <stderr@@GLIBC_2.2.5>
  401a36:	b8 00 00 00 00       	mov    $0x0,%eax
  401a3b:	e8 b0 f2 ff ff       	callq  400cf0 <__fprintf_chk@plt>
  401a40:	bf 01 00 00 00       	mov    $0x1,%edi
  401a45:	e8 86 f2 ff ff       	callq  400cd0 <exit@plt>

0000000000401a4a <rio_readlineb>:
  401a4a:	41 56                	push   %r14
  401a4c:	41 55                	push   %r13
  401a4e:	41 54                	push   %r12
  401a50:	55                   	push   %rbp
  401a51:	53                   	push   %rbx
  401a52:	48 83 ec 10          	sub    $0x10,%rsp
  401a56:	48 89 fb             	mov    %rdi,%rbx
  401a59:	49 89 f5             	mov    %rsi,%r13
  401a5c:	49 89 d6             	mov    %rdx,%r14
  401a5f:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401a66:	00 00 
  401a68:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  401a6d:	31 c0                	xor    %eax,%eax
  401a6f:	41 bc 01 00 00 00    	mov    $0x1,%r12d
  401a75:	48 8d 6f 10          	lea    0x10(%rdi),%rbp
  401a79:	48 83 fa 01          	cmp    $0x1,%rdx
  401a7d:	77 2c                	ja     401aab <rio_readlineb+0x61>
  401a7f:	eb 6d                	jmp    401aee <rio_readlineb+0xa4>
  401a81:	ba 00 20 00 00       	mov    $0x2000,%edx
  401a86:	48 89 ee             	mov    %rbp,%rsi
  401a89:	8b 3b                	mov    (%rbx),%edi
  401a8b:	e8 80 f1 ff ff       	callq  400c10 <read@plt>
  401a90:	89 43 04             	mov    %eax,0x4(%rbx)
  401a93:	85 c0                	test   %eax,%eax
  401a95:	79 0c                	jns    401aa3 <rio_readlineb+0x59>
  401a97:	e8 04 f1 ff ff       	callq  400ba0 <__errno_location@plt>
  401a9c:	83 38 04             	cmpl   $0x4,(%rax)
  401a9f:	74 0a                	je     401aab <rio_readlineb+0x61>
  401aa1:	eb 6c                	jmp    401b0f <rio_readlineb+0xc5>
  401aa3:	85 c0                	test   %eax,%eax
  401aa5:	74 71                	je     401b18 <rio_readlineb+0xce>
  401aa7:	48 89 6b 08          	mov    %rbp,0x8(%rbx)
  401aab:	8b 43 04             	mov    0x4(%rbx),%eax
  401aae:	85 c0                	test   %eax,%eax
  401ab0:	7e cf                	jle    401a81 <rio_readlineb+0x37>
  401ab2:	48 8b 53 08          	mov    0x8(%rbx),%rdx
  401ab6:	0f b6 0a             	movzbl (%rdx),%ecx
  401ab9:	88 4c 24 07          	mov    %cl,0x7(%rsp)
  401abd:	48 83 c2 01          	add    $0x1,%rdx
  401ac1:	48 89 53 08          	mov    %rdx,0x8(%rbx)
  401ac5:	83 e8 01             	sub    $0x1,%eax
  401ac8:	89 43 04             	mov    %eax,0x4(%rbx)
  401acb:	49 83 c5 01          	add    $0x1,%r13
  401acf:	41 88 4d ff          	mov    %cl,-0x1(%r13)
  401ad3:	80 f9 0a             	cmp    $0xa,%cl
  401ad6:	75 0a                	jne    401ae2 <rio_readlineb+0x98>
  401ad8:	eb 14                	jmp    401aee <rio_readlineb+0xa4>
  401ada:	41 83 fc 01          	cmp    $0x1,%r12d
  401ade:	75 0e                	jne    401aee <rio_readlineb+0xa4>
  401ae0:	eb 16                	jmp    401af8 <rio_readlineb+0xae>
  401ae2:	41 83 c4 01          	add    $0x1,%r12d
  401ae6:	49 63 c4             	movslq %r12d,%rax
  401ae9:	4c 39 f0             	cmp    %r14,%rax
  401aec:	72 bd                	jb     401aab <rio_readlineb+0x61>
  401aee:	41 c6 45 00 00       	movb   $0x0,0x0(%r13)
  401af3:	49 63 c4             	movslq %r12d,%rax
  401af6:	eb 05                	jmp    401afd <rio_readlineb+0xb3>
  401af8:	b8 00 00 00 00       	mov    $0x0,%eax
  401afd:	48 8b 4c 24 08       	mov    0x8(%rsp),%rcx
  401b02:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  401b09:	00 00 
  401b0b:	74 22                	je     401b2f <rio_readlineb+0xe5>
  401b0d:	eb 1b                	jmp    401b2a <rio_readlineb+0xe0>
  401b0f:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401b16:	eb 05                	jmp    401b1d <rio_readlineb+0xd3>
  401b18:	b8 00 00 00 00       	mov    $0x0,%eax
  401b1d:	85 c0                	test   %eax,%eax
  401b1f:	74 b9                	je     401ada <rio_readlineb+0x90>
  401b21:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401b28:	eb d3                	jmp    401afd <rio_readlineb+0xb3>
  401b2a:	e8 b1 f0 ff ff       	callq  400be0 <__stack_chk_fail@plt>
  401b2f:	48 83 c4 10          	add    $0x10,%rsp
  401b33:	5b                   	pop    %rbx
  401b34:	5d                   	pop    %rbp
  401b35:	41 5c                	pop    %r12
  401b37:	41 5d                	pop    %r13
  401b39:	41 5e                	pop    %r14
  401b3b:	c3                   	retq   

0000000000401b3c <submitr>:
  401b3c:	41 57                	push   %r15
  401b3e:	41 56                	push   %r14
  401b40:	41 55                	push   %r13
  401b42:	41 54                	push   %r12
  401b44:	55                   	push   %rbp
  401b45:	53                   	push   %rbx
  401b46:	48 81 ec 68 a0 00 00 	sub    $0xa068,%rsp
  401b4d:	49 89 fd             	mov    %rdi,%r13
  401b50:	89 f5                	mov    %esi,%ebp
  401b52:	48 89 14 24          	mov    %rdx,(%rsp)
  401b56:	48 89 4c 24 08       	mov    %rcx,0x8(%rsp)
  401b5b:	4c 89 44 24 18       	mov    %r8,0x18(%rsp)
  401b60:	4c 89 4c 24 10       	mov    %r9,0x10(%rsp)
  401b65:	48 8b 9c 24 a0 a0 00 	mov    0xa0a0(%rsp),%rbx
  401b6c:	00 
  401b6d:	4c 8b bc 24 a8 a0 00 	mov    0xa0a8(%rsp),%r15
  401b74:	00 
  401b75:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401b7c:	00 00 
  401b7e:	48 89 84 24 58 a0 00 	mov    %rax,0xa058(%rsp)
  401b85:	00 
  401b86:	31 c0                	xor    %eax,%eax
  401b88:	c7 44 24 2c 00 00 00 	movl   $0x0,0x2c(%rsp)
  401b8f:	00 
  401b90:	ba 00 00 00 00       	mov    $0x0,%edx
  401b95:	be 01 00 00 00       	mov    $0x1,%esi
  401b9a:	bf 02 00 00 00       	mov    $0x2,%edi
  401b9f:	e8 8c f1 ff ff       	callq  400d30 <socket@plt>
  401ba4:	85 c0                	test   %eax,%eax
  401ba6:	79 50                	jns    401bf8 <submitr+0xbc>
  401ba8:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401baf:	3a 20 43 
  401bb2:	49 89 07             	mov    %rax,(%r15)
  401bb5:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  401bbc:	20 75 6e 
  401bbf:	49 89 47 08          	mov    %rax,0x8(%r15)
  401bc3:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401bca:	74 6f 20 
  401bcd:	49 89 47 10          	mov    %rax,0x10(%r15)
  401bd1:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  401bd8:	65 20 73 
  401bdb:	49 89 47 18          	mov    %rax,0x18(%r15)
  401bdf:	41 c7 47 20 6f 63 6b 	movl   $0x656b636f,0x20(%r15)
  401be6:	65 
  401be7:	66 41 c7 47 24 74 00 	movw   $0x74,0x24(%r15)
  401bee:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401bf3:	e9 12 06 00 00       	jmpq   40220a <submitr+0x6ce>
  401bf8:	41 89 c4             	mov    %eax,%r12d
  401bfb:	4c 89 ef             	mov    %r13,%rdi
  401bfe:	e8 4d f0 ff ff       	callq  400c50 <gethostbyname@plt>
  401c03:	48 85 c0             	test   %rax,%rax
  401c06:	75 6b                	jne    401c73 <submitr+0x137>
  401c08:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  401c0f:	3a 20 44 
  401c12:	49 89 07             	mov    %rax,(%r15)
  401c15:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  401c1c:	20 75 6e 
  401c1f:	49 89 47 08          	mov    %rax,0x8(%r15)
  401c23:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401c2a:	74 6f 20 
  401c2d:	49 89 47 10          	mov    %rax,0x10(%r15)
  401c31:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  401c38:	76 65 20 
  401c3b:	49 89 47 18          	mov    %rax,0x18(%r15)
  401c3f:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  401c46:	72 20 61 
  401c49:	49 89 47 20          	mov    %rax,0x20(%r15)
  401c4d:	41 c7 47 28 64 64 72 	movl   $0x65726464,0x28(%r15)
  401c54:	65 
  401c55:	66 41 c7 47 2c 73 73 	movw   $0x7373,0x2c(%r15)
  401c5c:	41 c6 47 2e 00       	movb   $0x0,0x2e(%r15)
  401c61:	44 89 e7             	mov    %r12d,%edi
  401c64:	e8 97 ef ff ff       	callq  400c00 <close@plt>
  401c69:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401c6e:	e9 97 05 00 00       	jmpq   40220a <submitr+0x6ce>
  401c73:	48 c7 44 24 30 00 00 	movq   $0x0,0x30(%rsp)
  401c7a:	00 00 
  401c7c:	48 c7 44 24 38 00 00 	movq   $0x0,0x38(%rsp)
  401c83:	00 00 
  401c85:	66 c7 44 24 30 02 00 	movw   $0x2,0x30(%rsp)
  401c8c:	48 63 50 14          	movslq 0x14(%rax),%rdx
  401c90:	48 8b 40 18          	mov    0x18(%rax),%rax
  401c94:	48 8d 7c 24 34       	lea    0x34(%rsp),%rdi
  401c99:	b9 0c 00 00 00       	mov    $0xc,%ecx
  401c9e:	48 8b 30             	mov    (%rax),%rsi
  401ca1:	e8 ba ef ff ff       	callq  400c60 <__memmove_chk@plt>
  401ca6:	66 c1 cd 08          	ror    $0x8,%bp
  401caa:	66 89 6c 24 32       	mov    %bp,0x32(%rsp)
  401caf:	ba 10 00 00 00       	mov    $0x10,%edx
  401cb4:	48 8d 74 24 30       	lea    0x30(%rsp),%rsi
  401cb9:	44 89 e7             	mov    %r12d,%edi
  401cbc:	e8 1f f0 ff ff       	callq  400ce0 <connect@plt>
  401cc1:	85 c0                	test   %eax,%eax
  401cc3:	79 5d                	jns    401d22 <submitr+0x1e6>
  401cc5:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  401ccc:	3a 20 55 
  401ccf:	49 89 07             	mov    %rax,(%r15)
  401cd2:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  401cd9:	20 74 6f 
  401cdc:	49 89 47 08          	mov    %rax,0x8(%r15)
  401ce0:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  401ce7:	65 63 74 
  401cea:	49 89 47 10          	mov    %rax,0x10(%r15)
  401cee:	48 b8 20 74 6f 20 74 	movabs $0x20656874206f7420,%rax
  401cf5:	68 65 20 
  401cf8:	49 89 47 18          	mov    %rax,0x18(%r15)
  401cfc:	41 c7 47 20 73 65 72 	movl   $0x76726573,0x20(%r15)
  401d03:	76 
  401d04:	66 41 c7 47 24 65 72 	movw   $0x7265,0x24(%r15)
  401d0b:	41 c6 47 26 00       	movb   $0x0,0x26(%r15)
  401d10:	44 89 e7             	mov    %r12d,%edi
  401d13:	e8 e8 ee ff ff       	callq  400c00 <close@plt>
  401d18:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401d1d:	e9 e8 04 00 00       	jmpq   40220a <submitr+0x6ce>
  401d22:	49 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%r9
  401d29:	b8 00 00 00 00       	mov    $0x0,%eax
  401d2e:	4c 89 c9             	mov    %r9,%rcx
  401d31:	48 89 df             	mov    %rbx,%rdi
  401d34:	f2 ae                	repnz scas %es:(%rdi),%al
  401d36:	48 f7 d1             	not    %rcx
  401d39:	48 89 ce             	mov    %rcx,%rsi
  401d3c:	4c 89 c9             	mov    %r9,%rcx
  401d3f:	48 8b 3c 24          	mov    (%rsp),%rdi
  401d43:	f2 ae                	repnz scas %es:(%rdi),%al
  401d45:	49 89 c8             	mov    %rcx,%r8
  401d48:	4c 89 c9             	mov    %r9,%rcx
  401d4b:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401d50:	f2 ae                	repnz scas %es:(%rdi),%al
  401d52:	48 f7 d1             	not    %rcx
  401d55:	48 89 ca             	mov    %rcx,%rdx
  401d58:	4c 89 c9             	mov    %r9,%rcx
  401d5b:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  401d60:	f2 ae                	repnz scas %es:(%rdi),%al
  401d62:	4c 29 c2             	sub    %r8,%rdx
  401d65:	48 29 ca             	sub    %rcx,%rdx
  401d68:	48 8d 44 76 fd       	lea    -0x3(%rsi,%rsi,2),%rax
  401d6d:	48 8d 44 02 7b       	lea    0x7b(%rdx,%rax,1),%rax
  401d72:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
  401d78:	76 73                	jbe    401ded <submitr+0x2b1>
  401d7a:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  401d81:	3a 20 52 
  401d84:	49 89 07             	mov    %rax,(%r15)
  401d87:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  401d8e:	20 73 74 
  401d91:	49 89 47 08          	mov    %rax,0x8(%r15)
  401d95:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
  401d9c:	74 6f 6f 
  401d9f:	49 89 47 10          	mov    %rax,0x10(%r15)
  401da3:	48 b8 20 6c 61 72 67 	movabs $0x202e656772616c20,%rax
  401daa:	65 2e 20 
  401dad:	49 89 47 18          	mov    %rax,0x18(%r15)
  401db1:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
  401db8:	61 73 65 
  401dbb:	49 89 47 20          	mov    %rax,0x20(%r15)
  401dbf:	48 b8 20 53 55 42 4d 	movabs $0x5254494d42555320,%rax
  401dc6:	49 54 52 
  401dc9:	49 89 47 28          	mov    %rax,0x28(%r15)
  401dcd:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
  401dd4:	55 46 00 
  401dd7:	49 89 47 30          	mov    %rax,0x30(%r15)
  401ddb:	44 89 e7             	mov    %r12d,%edi
  401dde:	e8 1d ee ff ff       	callq  400c00 <close@plt>
  401de3:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401de8:	e9 1d 04 00 00       	jmpq   40220a <submitr+0x6ce>
  401ded:	48 8d 94 24 50 40 00 	lea    0x4050(%rsp),%rdx
  401df4:	00 
  401df5:	b9 00 04 00 00       	mov    $0x400,%ecx
  401dfa:	b8 00 00 00 00       	mov    $0x0,%eax
  401dff:	48 89 d7             	mov    %rdx,%rdi
  401e02:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  401e05:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401e0c:	48 89 df             	mov    %rbx,%rdi
  401e0f:	f2 ae                	repnz scas %es:(%rdi),%al
  401e11:	48 89 c8             	mov    %rcx,%rax
  401e14:	48 f7 d0             	not    %rax
  401e17:	48 83 e8 01          	sub    $0x1,%rax
  401e1b:	85 c0                	test   %eax,%eax
  401e1d:	0f 84 90 04 00 00    	je     4022b3 <submitr+0x777>
  401e23:	8d 40 ff             	lea    -0x1(%rax),%eax
  401e26:	4c 8d 74 03 01       	lea    0x1(%rbx,%rax,1),%r14
  401e2b:	48 89 d5             	mov    %rdx,%rbp
  401e2e:	49 bd d9 ff 00 00 00 	movabs $0x2000000000ffd9,%r13
  401e35:	00 20 00 
  401e38:	44 0f b6 03          	movzbl (%rbx),%r8d
  401e3c:	41 8d 40 d6          	lea    -0x2a(%r8),%eax
  401e40:	3c 35                	cmp    $0x35,%al
  401e42:	77 06                	ja     401e4a <submitr+0x30e>
  401e44:	49 0f a3 c5          	bt     %rax,%r13
  401e48:	72 0d                	jb     401e57 <submitr+0x31b>
  401e4a:	44 89 c0             	mov    %r8d,%eax
  401e4d:	83 e0 df             	and    $0xffffffdf,%eax
  401e50:	83 e8 41             	sub    $0x41,%eax
  401e53:	3c 19                	cmp    $0x19,%al
  401e55:	77 0a                	ja     401e61 <submitr+0x325>
  401e57:	44 88 45 00          	mov    %r8b,0x0(%rbp)
  401e5b:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  401e5f:	eb 6c                	jmp    401ecd <submitr+0x391>
  401e61:	41 80 f8 20          	cmp    $0x20,%r8b
  401e65:	75 0a                	jne    401e71 <submitr+0x335>
  401e67:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
  401e6b:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  401e6f:	eb 5c                	jmp    401ecd <submitr+0x391>
  401e71:	41 8d 40 e0          	lea    -0x20(%r8),%eax
  401e75:	3c 5f                	cmp    $0x5f,%al
  401e77:	76 0a                	jbe    401e83 <submitr+0x347>
  401e79:	41 80 f8 09          	cmp    $0x9,%r8b
  401e7d:	0f 85 a3 03 00 00    	jne    402226 <submitr+0x6ea>
  401e83:	45 0f b6 c0          	movzbl %r8b,%r8d
  401e87:	b9 b0 2e 40 00       	mov    $0x402eb0,%ecx
  401e8c:	ba 08 00 00 00       	mov    $0x8,%edx
  401e91:	be 01 00 00 00       	mov    $0x1,%esi
  401e96:	48 8d bc 24 50 80 00 	lea    0x8050(%rsp),%rdi
  401e9d:	00 
  401e9e:	b8 00 00 00 00       	mov    $0x0,%eax
  401ea3:	e8 78 ee ff ff       	callq  400d20 <__sprintf_chk@plt>
  401ea8:	0f b6 84 24 50 80 00 	movzbl 0x8050(%rsp),%eax
  401eaf:	00 
  401eb0:	88 45 00             	mov    %al,0x0(%rbp)
  401eb3:	0f b6 84 24 51 80 00 	movzbl 0x8051(%rsp),%eax
  401eba:	00 
  401ebb:	88 45 01             	mov    %al,0x1(%rbp)
  401ebe:	0f b6 84 24 52 80 00 	movzbl 0x8052(%rsp),%eax
  401ec5:	00 
  401ec6:	88 45 02             	mov    %al,0x2(%rbp)
  401ec9:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
  401ecd:	48 83 c3 01          	add    $0x1,%rbx
  401ed1:	49 39 de             	cmp    %rbx,%r14
  401ed4:	0f 85 5e ff ff ff    	jne    401e38 <submitr+0x2fc>
  401eda:	e9 d4 03 00 00       	jmpq   4022b3 <submitr+0x777>
  401edf:	48 89 da             	mov    %rbx,%rdx
  401ee2:	48 89 ee             	mov    %rbp,%rsi
  401ee5:	44 89 e7             	mov    %r12d,%edi
  401ee8:	e8 e3 ec ff ff       	callq  400bd0 <write@plt>
  401eed:	48 85 c0             	test   %rax,%rax
  401ef0:	7f 0f                	jg     401f01 <submitr+0x3c5>
  401ef2:	e8 a9 ec ff ff       	callq  400ba0 <__errno_location@plt>
  401ef7:	83 38 04             	cmpl   $0x4,(%rax)
  401efa:	75 12                	jne    401f0e <submitr+0x3d2>
  401efc:	b8 00 00 00 00       	mov    $0x0,%eax
  401f01:	48 01 c5             	add    %rax,%rbp
  401f04:	48 29 c3             	sub    %rax,%rbx
  401f07:	75 d6                	jne    401edf <submitr+0x3a3>
  401f09:	4d 85 ed             	test   %r13,%r13
  401f0c:	79 5f                	jns    401f6d <submitr+0x431>
  401f0e:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401f15:	3a 20 43 
  401f18:	49 89 07             	mov    %rax,(%r15)
  401f1b:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  401f22:	20 75 6e 
  401f25:	49 89 47 08          	mov    %rax,0x8(%r15)
  401f29:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401f30:	74 6f 20 
  401f33:	49 89 47 10          	mov    %rax,0x10(%r15)
  401f37:	48 b8 77 72 69 74 65 	movabs $0x6f74206574697277,%rax
  401f3e:	20 74 6f 
  401f41:	49 89 47 18          	mov    %rax,0x18(%r15)
  401f45:	48 b8 20 74 68 65 20 	movabs $0x7265732065687420,%rax
  401f4c:	73 65 72 
  401f4f:	49 89 47 20          	mov    %rax,0x20(%r15)
  401f53:	41 c7 47 28 76 65 72 	movl   $0x726576,0x28(%r15)
  401f5a:	00 
  401f5b:	44 89 e7             	mov    %r12d,%edi
  401f5e:	e8 9d ec ff ff       	callq  400c00 <close@plt>
  401f63:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401f68:	e9 9d 02 00 00       	jmpq   40220a <submitr+0x6ce>
  401f6d:	44 89 64 24 40       	mov    %r12d,0x40(%rsp)
  401f72:	c7 44 24 44 00 00 00 	movl   $0x0,0x44(%rsp)
  401f79:	00 
  401f7a:	48 8d 44 24 50       	lea    0x50(%rsp),%rax
  401f7f:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  401f84:	ba 00 20 00 00       	mov    $0x2000,%edx
  401f89:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  401f90:	00 
  401f91:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  401f96:	e8 af fa ff ff       	callq  401a4a <rio_readlineb>
  401f9b:	48 85 c0             	test   %rax,%rax
  401f9e:	7f 74                	jg     402014 <submitr+0x4d8>
  401fa0:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401fa7:	3a 20 43 
  401faa:	49 89 07             	mov    %rax,(%r15)
  401fad:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  401fb4:	20 75 6e 
  401fb7:	49 89 47 08          	mov    %rax,0x8(%r15)
  401fbb:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401fc2:	74 6f 20 
  401fc5:	49 89 47 10          	mov    %rax,0x10(%r15)
  401fc9:	48 b8 72 65 61 64 20 	movabs $0x7269662064616572,%rax
  401fd0:	66 69 72 
  401fd3:	49 89 47 18          	mov    %rax,0x18(%r15)
  401fd7:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
  401fde:	61 64 65 
  401fe1:	49 89 47 20          	mov    %rax,0x20(%r15)
  401fe5:	48 b8 72 20 66 72 6f 	movabs $0x73206d6f72662072,%rax
  401fec:	6d 20 73 
  401fef:	49 89 47 28          	mov    %rax,0x28(%r15)
  401ff3:	41 c7 47 30 65 72 76 	movl   $0x65767265,0x30(%r15)
  401ffa:	65 
  401ffb:	66 41 c7 47 34 72 00 	movw   $0x72,0x34(%r15)
  402002:	44 89 e7             	mov    %r12d,%edi
  402005:	e8 f6 eb ff ff       	callq  400c00 <close@plt>
  40200a:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40200f:	e9 f6 01 00 00       	jmpq   40220a <submitr+0x6ce>
  402014:	4c 8d 84 24 50 80 00 	lea    0x8050(%rsp),%r8
  40201b:	00 
  40201c:	48 8d 4c 24 2c       	lea    0x2c(%rsp),%rcx
  402021:	48 8d 94 24 50 60 00 	lea    0x6050(%rsp),%rdx
  402028:	00 
  402029:	be b7 2e 40 00       	mov    $0x402eb7,%esi
  40202e:	48 8d bc 24 50 20 00 	lea    0x2050(%rsp),%rdi
  402035:	00 
  402036:	b8 00 00 00 00       	mov    $0x0,%eax
  40203b:	e8 50 ec ff ff       	callq  400c90 <__isoc99_sscanf@plt>
  402040:	44 8b 44 24 2c       	mov    0x2c(%rsp),%r8d
  402045:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
  40204c:	0f 84 be 00 00 00    	je     402110 <submitr+0x5d4>
  402052:	4c 8d 8c 24 50 80 00 	lea    0x8050(%rsp),%r9
  402059:	00 
  40205a:	b9 00 2e 40 00       	mov    $0x402e00,%ecx
  40205f:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  402066:	be 01 00 00 00       	mov    $0x1,%esi
  40206b:	4c 89 ff             	mov    %r15,%rdi
  40206e:	b8 00 00 00 00       	mov    $0x0,%eax
  402073:	e8 a8 ec ff ff       	callq  400d20 <__sprintf_chk@plt>
  402078:	44 89 e7             	mov    %r12d,%edi
  40207b:	e8 80 eb ff ff       	callq  400c00 <close@plt>
  402080:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402085:	e9 80 01 00 00       	jmpq   40220a <submitr+0x6ce>
  40208a:	ba 00 20 00 00       	mov    $0x2000,%edx
  40208f:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  402096:	00 
  402097:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  40209c:	e8 a9 f9 ff ff       	callq  401a4a <rio_readlineb>
  4020a1:	48 85 c0             	test   %rax,%rax
  4020a4:	7f 6a                	jg     402110 <submitr+0x5d4>
  4020a6:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4020ad:	3a 20 43 
  4020b0:	49 89 07             	mov    %rax,(%r15)
  4020b3:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4020ba:	20 75 6e 
  4020bd:	49 89 47 08          	mov    %rax,0x8(%r15)
  4020c1:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4020c8:	74 6f 20 
  4020cb:	49 89 47 10          	mov    %rax,0x10(%r15)
  4020cf:	48 b8 72 65 61 64 20 	movabs $0x6165682064616572,%rax
  4020d6:	68 65 61 
  4020d9:	49 89 47 18          	mov    %rax,0x18(%r15)
  4020dd:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
  4020e4:	66 72 6f 
  4020e7:	49 89 47 20          	mov    %rax,0x20(%r15)
  4020eb:	48 b8 6d 20 73 65 72 	movabs $0x726576726573206d,%rax
  4020f2:	76 65 72 
  4020f5:	49 89 47 28          	mov    %rax,0x28(%r15)
  4020f9:	41 c6 47 30 00       	movb   $0x0,0x30(%r15)
  4020fe:	44 89 e7             	mov    %r12d,%edi
  402101:	e8 fa ea ff ff       	callq  400c00 <close@plt>
  402106:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40210b:	e9 fa 00 00 00       	jmpq   40220a <submitr+0x6ce>
  402110:	80 bc 24 50 20 00 00 	cmpb   $0xd,0x2050(%rsp)
  402117:	0d 
  402118:	0f 85 6c ff ff ff    	jne    40208a <submitr+0x54e>
  40211e:	80 bc 24 51 20 00 00 	cmpb   $0xa,0x2051(%rsp)
  402125:	0a 
  402126:	0f 85 5e ff ff ff    	jne    40208a <submitr+0x54e>
  40212c:	80 bc 24 52 20 00 00 	cmpb   $0x0,0x2052(%rsp)
  402133:	00 
  402134:	0f 85 50 ff ff ff    	jne    40208a <submitr+0x54e>
  40213a:	ba 00 20 00 00       	mov    $0x2000,%edx
  40213f:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  402146:	00 
  402147:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  40214c:	e8 f9 f8 ff ff       	callq  401a4a <rio_readlineb>
  402151:	48 85 c0             	test   %rax,%rax
  402154:	7f 70                	jg     4021c6 <submitr+0x68a>
  402156:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  40215d:	3a 20 43 
  402160:	49 89 07             	mov    %rax,(%r15)
  402163:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  40216a:	20 75 6e 
  40216d:	49 89 47 08          	mov    %rax,0x8(%r15)
  402171:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402178:	74 6f 20 
  40217b:	49 89 47 10          	mov    %rax,0x10(%r15)
  40217f:	48 b8 72 65 61 64 20 	movabs $0x6174732064616572,%rax
  402186:	73 74 61 
  402189:	49 89 47 18          	mov    %rax,0x18(%r15)
  40218d:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
  402194:	65 73 73 
  402197:	49 89 47 20          	mov    %rax,0x20(%r15)
  40219b:	48 b8 61 67 65 20 66 	movabs $0x6d6f726620656761,%rax
  4021a2:	72 6f 6d 
  4021a5:	49 89 47 28          	mov    %rax,0x28(%r15)
  4021a9:	48 b8 20 73 65 72 76 	movabs $0x72657672657320,%rax
  4021b0:	65 72 00 
  4021b3:	49 89 47 30          	mov    %rax,0x30(%r15)
  4021b7:	44 89 e7             	mov    %r12d,%edi
  4021ba:	e8 41 ea ff ff       	callq  400c00 <close@plt>
  4021bf:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4021c4:	eb 44                	jmp    40220a <submitr+0x6ce>
  4021c6:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  4021cd:	00 
  4021ce:	4c 89 ff             	mov    %r15,%rdi
  4021d1:	e8 da e9 ff ff       	callq  400bb0 <strcpy@plt>
  4021d6:	44 89 e7             	mov    %r12d,%edi
  4021d9:	e8 22 ea ff ff       	callq  400c00 <close@plt>
  4021de:	41 0f b6 17          	movzbl (%r15),%edx
  4021e2:	b8 4f 00 00 00       	mov    $0x4f,%eax
  4021e7:	29 d0                	sub    %edx,%eax
  4021e9:	75 15                	jne    402200 <submitr+0x6c4>
  4021eb:	41 0f b6 57 01       	movzbl 0x1(%r15),%edx
  4021f0:	b8 4b 00 00 00       	mov    $0x4b,%eax
  4021f5:	29 d0                	sub    %edx,%eax
  4021f7:	75 07                	jne    402200 <submitr+0x6c4>
  4021f9:	41 0f b6 47 02       	movzbl 0x2(%r15),%eax
  4021fe:	f7 d8                	neg    %eax
  402200:	85 c0                	test   %eax,%eax
  402202:	0f 95 c0             	setne  %al
  402205:	0f b6 c0             	movzbl %al,%eax
  402208:	f7 d8                	neg    %eax
  40220a:	48 8b 8c 24 58 a0 00 	mov    0xa058(%rsp),%rcx
  402211:	00 
  402212:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402219:	00 00 
  40221b:	0f 84 12 01 00 00    	je     402333 <submitr+0x7f7>
  402221:	e9 08 01 00 00       	jmpq   40232e <submitr+0x7f2>
  402226:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  40222d:	3a 20 52 
  402230:	49 89 07             	mov    %rax,(%r15)
  402233:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  40223a:	20 73 74 
  40223d:	49 89 47 08          	mov    %rax,0x8(%r15)
  402241:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
  402248:	63 6f 6e 
  40224b:	49 89 47 10          	mov    %rax,0x10(%r15)
  40224f:	48 b8 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rax
  402256:	20 61 6e 
  402259:	49 89 47 18          	mov    %rax,0x18(%r15)
  40225d:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
  402264:	67 61 6c 
  402267:	49 89 47 20          	mov    %rax,0x20(%r15)
  40226b:	48 b8 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rax
  402272:	6e 70 72 
  402275:	49 89 47 28          	mov    %rax,0x28(%r15)
  402279:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
  402280:	6c 65 20 
  402283:	49 89 47 30          	mov    %rax,0x30(%r15)
  402287:	48 b8 63 68 61 72 61 	movabs $0x6574636172616863,%rax
  40228e:	63 74 65 
  402291:	49 89 47 38          	mov    %rax,0x38(%r15)
  402295:	66 41 c7 47 40 72 2e 	movw   $0x2e72,0x40(%r15)
  40229c:	41 c6 47 42 00       	movb   $0x0,0x42(%r15)
  4022a1:	44 89 e7             	mov    %r12d,%edi
  4022a4:	e8 57 e9 ff ff       	callq  400c00 <close@plt>
  4022a9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4022ae:	e9 57 ff ff ff       	jmpq   40220a <submitr+0x6ce>
  4022b3:	48 8d 9c 24 50 20 00 	lea    0x2050(%rsp),%rbx
  4022ba:	00 
  4022bb:	48 83 ec 08          	sub    $0x8,%rsp
  4022bf:	48 8d 84 24 58 40 00 	lea    0x4058(%rsp),%rax
  4022c6:	00 
  4022c7:	50                   	push   %rax
  4022c8:	ff 74 24 20          	pushq  0x20(%rsp)
  4022cc:	ff 74 24 30          	pushq  0x30(%rsp)
  4022d0:	4c 8b 4c 24 28       	mov    0x28(%rsp),%r9
  4022d5:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  4022da:	b9 30 2e 40 00       	mov    $0x402e30,%ecx
  4022df:	ba 00 20 00 00       	mov    $0x2000,%edx
  4022e4:	be 01 00 00 00       	mov    $0x1,%esi
  4022e9:	48 89 df             	mov    %rbx,%rdi
  4022ec:	b8 00 00 00 00       	mov    $0x0,%eax
  4022f1:	e8 2a ea ff ff       	callq  400d20 <__sprintf_chk@plt>
  4022f6:	b8 00 00 00 00       	mov    $0x0,%eax
  4022fb:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  402302:	48 89 df             	mov    %rbx,%rdi
  402305:	f2 ae                	repnz scas %es:(%rdi),%al
  402307:	48 89 c8             	mov    %rcx,%rax
  40230a:	48 f7 d0             	not    %rax
  40230d:	4c 8d 68 ff          	lea    -0x1(%rax),%r13
  402311:	48 83 c4 20          	add    $0x20,%rsp
  402315:	4c 89 eb             	mov    %r13,%rbx
  402318:	48 8d ac 24 50 20 00 	lea    0x2050(%rsp),%rbp
  40231f:	00 
  402320:	4d 85 ed             	test   %r13,%r13
  402323:	0f 85 b6 fb ff ff    	jne    401edf <submitr+0x3a3>
  402329:	e9 3f fc ff ff       	jmpq   401f6d <submitr+0x431>
  40232e:	e8 ad e8 ff ff       	callq  400be0 <__stack_chk_fail@plt>
  402333:	48 81 c4 68 a0 00 00 	add    $0xa068,%rsp
  40233a:	5b                   	pop    %rbx
  40233b:	5d                   	pop    %rbp
  40233c:	41 5c                	pop    %r12
  40233e:	41 5d                	pop    %r13
  402340:	41 5e                	pop    %r14
  402342:	41 5f                	pop    %r15
  402344:	c3                   	retq   

0000000000402345 <init_timeout>:
  402345:	85 ff                	test   %edi,%edi
  402347:	74 22                	je     40236b <init_timeout+0x26>
  402349:	53                   	push   %rbx
  40234a:	89 fb                	mov    %edi,%ebx
  40234c:	be 1c 1a 40 00       	mov    $0x401a1c,%esi
  402351:	bf 0e 00 00 00       	mov    $0xe,%edi
  402356:	e8 e5 e8 ff ff       	callq  400c40 <signal@plt>
  40235b:	85 db                	test   %ebx,%ebx
  40235d:	bf 00 00 00 00       	mov    $0x0,%edi
  402362:	0f 49 fb             	cmovns %ebx,%edi
  402365:	e8 86 e8 ff ff       	callq  400bf0 <alarm@plt>
  40236a:	5b                   	pop    %rbx
  40236b:	f3 c3                	repz retq 

000000000040236d <init_driver>:
  40236d:	55                   	push   %rbp
  40236e:	53                   	push   %rbx
  40236f:	48 83 ec 28          	sub    $0x28,%rsp
  402373:	48 89 fd             	mov    %rdi,%rbp
  402376:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40237d:	00 00 
  40237f:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  402384:	31 c0                	xor    %eax,%eax
  402386:	be 01 00 00 00       	mov    $0x1,%esi
  40238b:	bf 0d 00 00 00       	mov    $0xd,%edi
  402390:	e8 ab e8 ff ff       	callq  400c40 <signal@plt>
  402395:	be 01 00 00 00       	mov    $0x1,%esi
  40239a:	bf 1d 00 00 00       	mov    $0x1d,%edi
  40239f:	e8 9c e8 ff ff       	callq  400c40 <signal@plt>
  4023a4:	be 01 00 00 00       	mov    $0x1,%esi
  4023a9:	bf 1d 00 00 00       	mov    $0x1d,%edi
  4023ae:	e8 8d e8 ff ff       	callq  400c40 <signal@plt>
  4023b3:	ba 00 00 00 00       	mov    $0x0,%edx
  4023b8:	be 01 00 00 00       	mov    $0x1,%esi
  4023bd:	bf 02 00 00 00       	mov    $0x2,%edi
  4023c2:	e8 69 e9 ff ff       	callq  400d30 <socket@plt>
  4023c7:	85 c0                	test   %eax,%eax
  4023c9:	79 4f                	jns    40241a <init_driver+0xad>
  4023cb:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4023d2:	3a 20 43 
  4023d5:	48 89 45 00          	mov    %rax,0x0(%rbp)
  4023d9:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4023e0:	20 75 6e 
  4023e3:	48 89 45 08          	mov    %rax,0x8(%rbp)
  4023e7:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4023ee:	74 6f 20 
  4023f1:	48 89 45 10          	mov    %rax,0x10(%rbp)
  4023f5:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  4023fc:	65 20 73 
  4023ff:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402403:	c7 45 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbp)
  40240a:	66 c7 45 24 74 00    	movw   $0x74,0x24(%rbp)
  402410:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402415:	e9 0c 01 00 00       	jmpq   402526 <init_driver+0x1b9>
  40241a:	89 c3                	mov    %eax,%ebx
  40241c:	bf c8 2e 40 00       	mov    $0x402ec8,%edi
  402421:	e8 2a e8 ff ff       	callq  400c50 <gethostbyname@plt>
  402426:	48 85 c0             	test   %rax,%rax
  402429:	75 68                	jne    402493 <init_driver+0x126>
  40242b:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  402432:	3a 20 44 
  402435:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402439:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  402440:	20 75 6e 
  402443:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402447:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  40244e:	74 6f 20 
  402451:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402455:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  40245c:	76 65 20 
  40245f:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402463:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  40246a:	72 20 61 
  40246d:	48 89 45 20          	mov    %rax,0x20(%rbp)
  402471:	c7 45 28 64 64 72 65 	movl   $0x65726464,0x28(%rbp)
  402478:	66 c7 45 2c 73 73    	movw   $0x7373,0x2c(%rbp)
  40247e:	c6 45 2e 00          	movb   $0x0,0x2e(%rbp)
  402482:	89 df                	mov    %ebx,%edi
  402484:	e8 77 e7 ff ff       	callq  400c00 <close@plt>
  402489:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40248e:	e9 93 00 00 00       	jmpq   402526 <init_driver+0x1b9>
  402493:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  40249a:	00 
  40249b:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  4024a2:	00 00 
  4024a4:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  4024aa:	48 63 50 14          	movslq 0x14(%rax),%rdx
  4024ae:	48 8b 40 18          	mov    0x18(%rax),%rax
  4024b2:	48 8d 7c 24 04       	lea    0x4(%rsp),%rdi
  4024b7:	b9 0c 00 00 00       	mov    $0xc,%ecx
  4024bc:	48 8b 30             	mov    (%rax),%rsi
  4024bf:	e8 9c e7 ff ff       	callq  400c60 <__memmove_chk@plt>
  4024c4:	66 c7 44 24 02 1f 94 	movw   $0x941f,0x2(%rsp)
  4024cb:	ba 10 00 00 00       	mov    $0x10,%edx
  4024d0:	48 89 e6             	mov    %rsp,%rsi
  4024d3:	89 df                	mov    %ebx,%edi
  4024d5:	e8 06 e8 ff ff       	callq  400ce0 <connect@plt>
  4024da:	85 c0                	test   %eax,%eax
  4024dc:	79 32                	jns    402510 <init_driver+0x1a3>
  4024de:	41 b8 c8 2e 40 00    	mov    $0x402ec8,%r8d
  4024e4:	b9 88 2e 40 00       	mov    $0x402e88,%ecx
  4024e9:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  4024f0:	be 01 00 00 00       	mov    $0x1,%esi
  4024f5:	48 89 ef             	mov    %rbp,%rdi
  4024f8:	b8 00 00 00 00       	mov    $0x0,%eax
  4024fd:	e8 1e e8 ff ff       	callq  400d20 <__sprintf_chk@plt>
  402502:	89 df                	mov    %ebx,%edi
  402504:	e8 f7 e6 ff ff       	callq  400c00 <close@plt>
  402509:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40250e:	eb 16                	jmp    402526 <init_driver+0x1b9>
  402510:	89 df                	mov    %ebx,%edi
  402512:	e8 e9 e6 ff ff       	callq  400c00 <close@plt>
  402517:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
  40251d:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
  402521:	b8 00 00 00 00       	mov    $0x0,%eax
  402526:	48 8b 4c 24 18       	mov    0x18(%rsp),%rcx
  40252b:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402532:	00 00 
  402534:	74 05                	je     40253b <init_driver+0x1ce>
  402536:	e8 a5 e6 ff ff       	callq  400be0 <__stack_chk_fail@plt>
  40253b:	48 83 c4 28          	add    $0x28,%rsp
  40253f:	5b                   	pop    %rbx
  402540:	5d                   	pop    %rbp
  402541:	c3                   	retq   

0000000000402542 <driver_post>:
  402542:	53                   	push   %rbx
  402543:	4c 89 c3             	mov    %r8,%rbx
  402546:	85 c9                	test   %ecx,%ecx
  402548:	74 24                	je     40256e <driver_post+0x2c>
  40254a:	be e0 2e 40 00       	mov    $0x402ee0,%esi
  40254f:	bf 01 00 00 00       	mov    $0x1,%edi
  402554:	b8 00 00 00 00       	mov    $0x0,%eax
  402559:	e8 42 e7 ff ff       	callq  400ca0 <__printf_chk@plt>
  40255e:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402563:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402567:	b8 00 00 00 00       	mov    $0x0,%eax
  40256c:	eb 41                	jmp    4025af <driver_post+0x6d>
  40256e:	48 85 ff             	test   %rdi,%rdi
  402571:	74 2e                	je     4025a1 <driver_post+0x5f>
  402573:	80 3f 00             	cmpb   $0x0,(%rdi)
  402576:	74 29                	je     4025a1 <driver_post+0x5f>
  402578:	41 50                	push   %r8
  40257a:	52                   	push   %rdx
  40257b:	41 b9 f7 2e 40 00    	mov    $0x402ef7,%r9d
  402581:	49 89 f0             	mov    %rsi,%r8
  402584:	48 89 f9             	mov    %rdi,%rcx
  402587:	ba fb 2e 40 00       	mov    $0x402efb,%edx
  40258c:	be 94 1f 00 00       	mov    $0x1f94,%esi
  402591:	bf c8 2e 40 00       	mov    $0x402ec8,%edi
  402596:	e8 a1 f5 ff ff       	callq  401b3c <submitr>
  40259b:	48 83 c4 10          	add    $0x10,%rsp
  40259f:	eb 0e                	jmp    4025af <driver_post+0x6d>
  4025a1:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  4025a6:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  4025aa:	b8 00 00 00 00       	mov    $0x0,%eax
  4025af:	5b                   	pop    %rbx
  4025b0:	c3                   	retq   
  4025b1:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4025b8:	00 00 00 
  4025bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000004025c0 <__libc_csu_init>:
  4025c0:	41 57                	push   %r15
  4025c2:	41 56                	push   %r14
  4025c4:	41 89 ff             	mov    %edi,%r15d
  4025c7:	41 55                	push   %r13
  4025c9:	41 54                	push   %r12
  4025cb:	4c 8d 25 3e 18 20 00 	lea    0x20183e(%rip),%r12        # 603e10 <__frame_dummy_init_array_entry>
  4025d2:	55                   	push   %rbp
  4025d3:	48 8d 2d 3e 18 20 00 	lea    0x20183e(%rip),%rbp        # 603e18 <__init_array_end>
  4025da:	53                   	push   %rbx
  4025db:	49 89 f6             	mov    %rsi,%r14
  4025de:	49 89 d5             	mov    %rdx,%r13
  4025e1:	4c 29 e5             	sub    %r12,%rbp
  4025e4:	48 83 ec 08          	sub    $0x8,%rsp
  4025e8:	48 c1 fd 03          	sar    $0x3,%rbp
  4025ec:	e8 47 e5 ff ff       	callq  400b38 <_init>
  4025f1:	48 85 ed             	test   %rbp,%rbp
  4025f4:	74 20                	je     402616 <__libc_csu_init+0x56>
  4025f6:	31 db                	xor    %ebx,%ebx
  4025f8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4025ff:	00 
  402600:	4c 89 ea             	mov    %r13,%rdx
  402603:	4c 89 f6             	mov    %r14,%rsi
  402606:	44 89 ff             	mov    %r15d,%edi
  402609:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40260d:	48 83 c3 01          	add    $0x1,%rbx
  402611:	48 39 eb             	cmp    %rbp,%rbx
  402614:	75 ea                	jne    402600 <__libc_csu_init+0x40>
  402616:	48 83 c4 08          	add    $0x8,%rsp
  40261a:	5b                   	pop    %rbx
  40261b:	5d                   	pop    %rbp
  40261c:	41 5c                	pop    %r12
  40261e:	41 5d                	pop    %r13
  402620:	41 5e                	pop    %r14
  402622:	41 5f                	pop    %r15
  402624:	c3                   	retq   
  402625:	90                   	nop
  402626:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40262d:	00 00 00 

0000000000402630 <__libc_csu_fini>:
  402630:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000402634 <_fini>:
  402634:	48 83 ec 08          	sub    $0x8,%rsp
  402638:	48 83 c4 08          	add    $0x8,%rsp
  40263c:	c3                   	retq   
