import base64, subprocess, os, pathlib
'''base64 — нужен только ради функции a85encode, которая превращает «сырые» байты в строку ASCII-85.
os — генерация случайных данных (os.urandom).
subprocess — запуск собранной программы как отдельного процесса и получение её кода завершения/вывода.
pathlib — удобная работа с путями (Path('build') / 'ascii85_cli').
'''
BIN = "./ascii85_cli"   # ← имя итогового бинаря после сборки
def correct_data_test():
    raw = os.urandom(50)
    ascii85 = base64.a85encode(raw)
    r = subprocess.run([BIN], input=ascii85, stdout=subprocess.PIPE)
    print("correct exit code =", r.returncode)

def invalid_data_test():
    bad = b"!!! invalid***data !!!~>"      # добавили ~>
    r   = subprocess.run([BIN], input=bad, stdout=subprocess.PIPE)
    print("invalid exit code =", r.returncode)

correct_data_test()
invalid_data_test()
