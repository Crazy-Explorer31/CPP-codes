print(64, 192)
i = 0
for a in [0, 1]:
    for b in [0, 1]:
        for c in [0, 1]:
            for d in [0, 1]:
                for e in [0, 1]:
                    for f in [0, 1]:
                        if (a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f < 
                            ((a + 1) % 2) * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f):
                                i += 1
                                print(a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f, 
                                              ((a + 1) % 2) * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f)
                                
                        if (a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f < 
                            a * 32 + ((b + 1) % 2) * 16 + c * 8 + d * 4 + e * 2 + f):
                                i += 1
                                print(a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f, 
                                              a * 32 + ((b + 1) % 2) * 16 + c * 8 + d * 4 + e * 2 + f)
                                
                        if (a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f < 
                            a * 32 + b * 16 + ((c + 1) % 2) * 8 + d * 4 + e * 2 + f):
                                i += 1
                                print(a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f, 
                                              a * 32 + b * 16 + ((c + 1) % 2) * 8 + d * 4 + e * 2 + f)
                                
                        if (a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f < 
                            a * 32 + b * 16 + c * 8 + ((d + 1) % 2) * 4 + e * 2 + f):
                                i += 1
                                print(a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f, 
                                              a * 32 + b * 16 + c * 8 + ((d + 1) % 2) * 4 + e * 2 + f)
                                
                        if (a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f < 
                            a * 32 + b * 16 + c * 8 + d * 4 + ((e + 1) % 2) * 2 + f):
                                i += 1
                                print(a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f, 
                                              a * 32 + b * 16 + c * 8 + d * 4 + ((e + 1) % 2) * 2 + f)
                                
                        if (a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f < 
                            a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + ((f + 1) % 2)):
                                i += 1
                                print(a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + f, 
                                              a * 32 + b * 16 + c * 8 + d * 4 + e * 2 + ((f + 1) % 2))
                           