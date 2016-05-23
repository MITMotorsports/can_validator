// #ifndef ID
// 	#define ID 1
// #endif

// #define DEFINE_MAIN(x) main_ ## x
// #define main DEFINE_MAIN(ID)

// void main(){
// 	return 0;
// }


#define STRINGIFY2( x) #x
#define STRINGIFY(x) STRINGIFY2(x)
#define PASTE2( a, b) a##b
#define PASTE( a, b) PASTE2( a, b)

#define main PASTE(main_,ID)

// 
void main(void)
{
    return;
}

