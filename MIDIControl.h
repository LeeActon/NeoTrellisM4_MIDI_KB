#pragma once

class MIDIControl
	{
	protected:
		int code;
		int value;
		int min;
		int max;
		int mid;
		float zeroThreshold;
		int deltaThreshold;
		const char* name;

	public:
		MIDIControl(int code, int min, int max, const char* name)
			{
			this->code = code;
			SetMinMax(min, max);
			this->name = name;
			this->zeroThreshold = 2.0;
			this->deltaThreshold = 3;
			}

		void SetMinMax(int min, int max)
			{
			this->min = min;
			this->max = max;
			this->mid = (this->max - this->min) / 2;
			this->value = this->mid;
			}

		virtual void SendMIDI()
			{
			neoTrellisM4.controlChange(this->code, this->value);
			}

		void Update(float floatValue)
			{
			int newValue;

			if (abs(floatValue) < this->zeroThreshold)
				{
				newValue = (this->max - this->min) / 2;
				}
			else
				{
				newValue = Map(floatValue);
				}

			if (abs(newValue - this->value) >= this->deltaThreshold)
				{
				this->value = newValue;
				Serial.print(name);
				Serial.print(": ");
				Serial.println(this->value);
				SendMIDI();
				}
			}

		float Map(float inValue)
			{
			float inMin;
			float inMax;
			float outMin;
			float outMax;

			if (inValue > 0)
				{
				inMin = this->zeroThreshold;
				inMax = 10.0;
				outMin = this->mid;
				outMax = this->min;
				}
			else
				{
				inMin = -this->zeroThreshold;
				inMax = -10.0;
				outMin = this->mid;
				outMax = this->max;
				}
			float outValue = outMin + (inValue - inMin) / (inMax - inMin) * (outMax - outMin);

			if (outMax < outMin)
				{
				if (outValue < outMax)
					outValue = outMax;
				else if (outValue > outMin)
					outValue = outMin;
				}
			else
				{
				if (outValue > outMax)
					outValue = outMax;
				else if (outValue < outMin)
					outValue = outMin;
				}

			return outValue;
			}
	};
