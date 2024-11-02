# HTML Home Work 4 Code
### B13902149 高翊恩
### last edit: 2024/11/02
---

## Main script (SGD algorithm & linear transform)
```
g++ -std=c++17 ./main1.cpp -D PRINT
./a.out output.txt < data.txt
g++ -std=c++17 ./main2.cpp -D PRINT
./a.out E_in.txt E_out.txt < data.txt
```

## Generate Figure
```
python3 -m venv ./python
./python/bin/pip install matplotlib PyQt6
./python/bin/python ./python/plot_10.py figure_10.png < output.txt
./python/bin/python ./python/plot_11.py figure_11.png < E_in.txt
./python/bin/python ./python/plot_12.py figure_12.png < E_out.txt
```
