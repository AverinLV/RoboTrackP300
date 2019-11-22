/*
 * ���� ������ ����������� �������� ������� � ��������� ������ �������� ������
 * 
 * ��� ������������:
 * ������� ������ ���� Filter. �������� 2 ������������.
 * ���� ������������ ��� �������� LPF � HPF, ������ - ��� �������� BPF.
 * ��������� ��� ������������� ���������:
 * 
 * 		// ������ ��� LPF ��� HPF:
 * 		Filter(filterType filt_t, int num_taps, double Fs, double Fx);
 * 		// ������ ��� BPF:
 * 		Filter(filterType filt_t, int num_taps, double Fs, double Fl, double Fu);
 * 
 * ���������:
 * filt_t: ��� �������: LPF, HPF ��� BPF (LPF - �������������� ������, HPF - ��������������� ������, BPF - ��������� ������)
 * num_taps: ���������� �������, ������� �� ������ ������������ ������
 * Fs: ������� ������������� ����������� �������� ������
 * Fx: ������� �������� ��� �������� LPF � HPF
 * Fl, Fu: ������� � ������ ������� �������� ��� �������� BPF
 * 
 * ����� �������� ������� �� ������ ������ ���������� ������. 
 * ��� ������ 51-�������� �������������� ���������� ������ � 
 * �������� ������������� 44,1 ��� (������� ������������� CD), 
 * ��� ����� �������� �������� ������� ����������� ������ ����������� (4 ���):
 * 
 * Filter *my_filter;
 * 
 * my_filter = new Filter(LPF, 51, 44.1, 4.0)
 * if( my_filter->get_error_flag() != 0 ) // abort in an appropriate manner
 * 
 * while(data_to_be_filtered){
 * 	next_sample = // Get the next sample from the data stream somehow
 * 	filtered_sample = my_filter->do_sample( next_sample );
 *   .
 * 	.
 * 	.
 * }
 * delete my_filter;
 * 
 * ������������� ��������� ��������������� �������:
 *     init(): ������ ����� �������� ���������������� � ������� ������ ���� �������.
 *     get_taps(double *taps): returns the filter taps in the array "taps"
 *     write_taps_to_file(char *filename): ���������� ������ � ����
 *     write_freqres_to_file(char *filename): ������� ��������� �������������� � ����
 * 
 * �������, ��������������� ������� get_error_flag ().  ������������� ������������ 
 * ��� �������� ������������� ��������: get_error_flag () ������ ���������� ������� �������� ����� �������� ������ ������� Filter.  
 * ���� ��� ���������, ���������� �� ��������� �������, ����� ������ ����� ������:
 * -1:  Fs <= 0
 * -2:  Fx <= 0 or Fx >= Fs/2
 * -3:  num_taps <= 0 or num_taps >= MAX_NUM_FILTER_TAPS
 * -4:  �� ������� �������� ������ ��� ����������� ��������
 * -5:  �������� filterType ��� ������� � �����������
 * -10: Fs <= 0 (��� ������ BPF)
 * -11: Fl >= Fu
 * -12: Fl <= 0 || Fl >= Fs/2
 * -13: Fu <= 0 || Fu >= Fs/2
 * -14: num_taps <= 0 or num_taps >= MAX_NUM_FILTER_TAPS (��� ������ BPF)
 * -15:  �� ������� �������� ������ ��� ����������� �������� (��� ������ BPF)
 * -16:  �������� filterType ��� ������� � ����������� (��� ������ BPF)
 * 
 * Note that if a non-zero error code value occurs, every call to do_sample()
 * will return the value 0. write_taps_fo_file() will fail and return a -1 (it
 * also returns a -1 if it fails to open the tap file passed into it).
 * get_taps() will have no effect on the array passed in if the error_flag
 * is non-zero. write_freqres_to_file( ) returns different error codes
 * depending on the nature of the error...see the function itself for details.
 * 
 * ������� ����������� � �������������� ������� ����� �����. 
 * ��� ��������, ��� ������������ ����������� ���� ����� � ��������� �������������� 
 * ���������� ������� (LPF, HPF, BPF) ������������ � �������� ������� �������. 
 * ������������ ������� ����� ��������� ��������� � ������ ����������� ��-�� ������� ������; 
 * ������� �������� ����.
 */

#ifndef _FILTER_H
#define _FILTER_H

#define MAX_NUM_FILTER_TAPS 1000

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

enum filterType {LPF, HPF, BPF};

class Filter{
	private:
		filterType m_filt_t;
		int m_num_taps;
		int m_error_flag;
		double m_Fs;
		double m_Fx;
		double m_lambda;
		double *m_taps;
		double *m_sr;
		void designLPF();
		void designHPF();

		// Only needed for the bandpass filter case
		double m_Fu, m_phi;
		void designBPF();

	public:
		Filter(filterType filt_t, int num_taps, double Fs, double Fx);
		Filter(filterType filt_t, int num_taps, double Fs, double Fl, double Fu);
		~Filter( );
		void init();
		double do_sample(double data_sample);
		int get_error_flag(){return m_error_flag;};
		void get_taps( double *taps );
};

#endif
