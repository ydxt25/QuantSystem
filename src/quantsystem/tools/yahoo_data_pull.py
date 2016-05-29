#!/usr/bin/python
"""Download or update Yahoo CSV Data

This will download and update stock CSV data
whose name come from file from Yahoo.

Usage:
    [-d] Just download the stock CSV data to the --download_dir.
    [-u] Just update the stock CSV data to the --download_dir.
    [--download_dir=<path>] Sepceifies the download_dir.
                            The default path is ./.
"""

import os
import argparse
import urllib2
import threading

def generate_symbols():
    """generate stock symbols from 0001 to 8356"""
    # pylint: disable-msg=C0103
    MAX_SYM_NUM = 8356
    sym_list = [None] * MAX_SYM_NUM
    for i in range(1, MAX_SYM_NUM + 1):
        sym_list[i - 1] = "{0:04d}".format(i)
    return sym_list

def download_yahoo_data(download_dir, symbols_list):
    """Download stock data from Yahoo
    Args:
      download_dir: (string) dir to place the files.
      symbols_list: (list) list of symbols to read from Yahoo.
    """
    if not os.access(download_dir, os.F_OK):
        os.makedirs(download_dir)
    missing_symbols_list = []
    for symbol in symbols_list:
        symbol_name = symbol
        symbol += '.hk'
        try:
            url = 'http://ichart.finance.yahoo.com/table.csv?s=%s' % symbol
            response = urllib2.urlopen(url)
            page_data = response.read()
            with open(download_dir + symbol_name + '.csv', 'w') as outfile:
                outfile.write(page_data)
        except urllib2.HTTPError:
            missing_symbols_list.append(symbol_name)
            print 'Unable to fetch data for ' \
            'stock:{0} at {1}'.format(symbol_name, url)
        except urllib2.URLError:
            missing_symbols_list.append(symbol_name)
            print 'URL Error for stock: {0} at {1}'.format(symbol_name, url)
    return missing_symbols_list

def update_yahoo_data(root_dir):
    print 'a'

def read_symbols(file_name):
    """Read stock symbols from file
    Args:
      file_name: (string) input file name.
    """
    symbols_list = []
    with open(file_name, 'r') as infile:
        for line in infile.readlines():
            str_line = str(line).strip()
            if str_line:
                symbols_list.append(str_line)
    return symbols_list

def one_thread_download(download_dir, symbols_list):
    """Download stock data from Yahoo
    Args:
      download_dir: (string) dir to place the files.
      symbols_list: (list) list of symbols to read from Yahoo.
    """
    missing_symbols_list = download_yahoo_data(download_dir, symbols_list)
    # try again for missing
    download_yahoo_data(download_dir, missing_symbols_list)

def multi_thread_download(download_dir, symbols_list, num_threads=4):
    """Download stock data from Yahoo
    Args:
      download_dir: (string) dir to place the files.
      symbols_list: (list) list of symbols to read from Yahoo.
      num_threads: (int) number of threads.
    """
    threads = []
    symbols_per_thread = len(symbols_list) / num_threads
    for i in range(num_threads - 1):
        start = i * symbols_per_thread
        end = (i+1) * symbols_per_thread
        t = threading.Thread(target=one_thread_download,
                             args=(download_dir,
                                   symbols_list[start : end],))
        threads.append(t)
        t.start()
    start = symbols_per_thread * (num_threads - 1)
    t = threading.Thread(target=one_thread_download,
                             args=(download_dir,
                                   symbols_list[start: ],))
    threads.append(t)
    t.start()
    for t in threads:
        t.join()

def parse_argument():
    """Command line option and argument parsing."""
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument('-d', action='store_true', default=True,
                       dest='download',
                       help='Download the stock CSV data')
    group.add_argument('-u', action='store_true', default=False,
                       dest='update',
                       help='Update the stock CSV data')
    parser.add_argument('-f', action='store', default='',
                        dest='symbols_file',
                        help='Stock symbol name list')
    parser.add_argument('-t', action='store_true', default=False,
                        dest='multi_thread',
                        help='Mutlithread download or update stock data')
    parser.add_argument('--download_dir', '-r', action='store',
                        default='./', dest='dir',
                        help='Download dir')
    return parser.parse_args()

def main():
    """main function"""
    results = parse_argument()
    if results.symbols_file == '':
        symbols_list = generate_symbols()
    else:
        symbols_list = read_symbols(results.symbols_file)
    if results.download:
        if results.multi_thread:
            multi_thread_download(results.dir, symbols_list)
        else:
            one_thread_download(results.dir, symbols_list)
    else:
        if results.multi_thread:
            update_yahoo_data(results.dir)
        else:
            update_yahoo_data(results.dir)

if __name__ == '__main__':
    main()
