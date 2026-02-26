# Virtual Memory Simulator (vmsim)

## Purpose

This project is a command-line simulator for **virtual memory management** using **pure demand paging**.

It allows you to compare the behavior of three classic page replacement algorithms:

- FIFO (First-In, First-Out)
- LRU (Least Recently Used)
- Optimal

By running memory access traces, the simulator shows page hits, page faults, and page replacements, helping illustrate how different algorithms impact memory performance.

---

## How to Run

```bash
vmsim -a <fifo | optimal | lru> -n <number_of_frames> -f <trace_file>
```

### Options

- `-a` — Page replacement algorithm  
- `-n` — Number of physical memory frames (must be greater than 0)  
- `-f` — Trace file containing hexadecimal memory addresses  

### Example

```bash
vmsim -a lru -n 4 -f trace.dat
```
