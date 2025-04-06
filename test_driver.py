import base64
import subprocess
import os

Decoder = "./decoder_alg"
def correct_data_test():
    data = os.urandom(50)
    encoded = base64.a85encode(data)
    
    with open("input.txt", "wb") as f:
        f.write(encoded)
        
    result = subprocess.run([Decoder], stdin=open("input.txt", "rb"), stdout=subprocess.PIPE)
    print("correct data: exit code = ", result.returncode)
    
def invalid_data_test():
    with open("input.txt", "wb") as f:
        f.write(b"!!!***invalid***data***!!!")
    result = subpricess.run([Decoder], stdin=open("input.txt", "rb"), stdout=subprocess.PIPE)
    print("invalid data: exit code = ", result.returncode)
    
correct_data_test()
invalid_data_test()
