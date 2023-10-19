cnn_model = "googlelenet"
dtype = "float32"
arch = "avx2"

if dtype == "float16" and arch == "neon":
    uks = ["8x8", "8x16", "8x24", "8x32", "8x40", "8x48", 
           "16x8", "16x16", "16x24", "24x8", "32x8", "40x8", "48x8"]
elif dtype == "float64" and arch == "neon":
    uks = ["2x2", "2x4", "2x6", "2x8", "2x10", "2x12", 
           "4x2", "4x4", "4x6", "6x2", "8x2", "10x2", "12x2"]
elif dtype == "float32" and arch == "neon":
    uks = ["4x4", "4x8", "4x12", "4x16", "4x20", "4x24", 
           "8x4", "8x8", "8x12", "12x4", "16x4", "20x4", "24x4"]
elif dtype == "float16" and arch == "avx2":
    uks = ["16x16", "16x32", "16x48", "16x64", "16x80", "16x96", 
           "32x16", "32x32", "32x48", "48x16", "64x16", "80x16", "96x16"]
elif dtype == "float64" and arch == "avx2":
    uks = ["4x4", "4x8", "4x12", "4x16", "4x20", "4x24", 
           "8x4", "8x8", "8x12", "12x4", "16x4", "20x4", "24x4"]
elif dtype == "float32" and arch == "avx2":
    uks = ["8x8", "8x16", "8x24", "8x32", "8x40", "8x48", 
           "16x8", "16x16", "16x24", "24x8", "32x8", "40x8", "48x8"]
else:
    uks = ["4x4", "4x8", "4x12", "4x16", "4x20", "4x24", 
           "8x4", "8x8", "8x12", "12x4", "16x4", "20x4", "24x4"]
    
    
size = 9    # VGG
size = 53   # Googlelenet

best_uk = [(uks[0], 0)] * size

    

for uk in uks:
    path = 'out/{}/{}/{}_{}.csv'.format(dtype, cnn_model, cnn_model, uk)
    with open(path, 'r') as file:
        lines = file.readlines()
        for layer, line in enumerate(lines, start=-1):
            if line[0] != "#":
                gflops = float(line[-9:])
                if gflops > best_uk[layer][1]:
                    best_uk[layer] = uk, gflops, layer + 1
                    #print(best_uk)
    

print("# uk gflops layer")
for layer in best_uk:
    print(' '.join(str(element) for element in layer))
    
